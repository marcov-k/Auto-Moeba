#include <format>
#include <omp.h>

#include "Auto-Moeba.h"
#include "SaveSystem/Saver.h"
#include "Particles.h"
#include "Button.h"
#include "ParticleHandler.h"

int main()
{
	const int width = 1850;
	const int height = 900;

	InitWindow(width, height, "Auto-Moeba");
	SetTargetFPS(Simulation::_target_fps);

	Simulation::render_loop(width, height);
}

vector<Button> Simulation::particle_buttons;
int Simulation::selected_particle = 0;
bool Simulation::paused = true;
bool Simulation::controls_open = false;
bool Simulation::can_spawn = true;
float Simulation::spawn_timer = 0.0f;
float Simulation::warning_timer = Simulation::_warning_time;
int Simulation::warning_skip_frames = 0;
string Simulation::warning_text = "";


void Simulation::render_loop(int window_width, int window_height)
{
	Camera2D camera = { 0 };
	camera.offset = { window_width / 2.0f, window_height / 2.0f };
	camera.target = { 0.0f, 0.0f };
	camera.zoom = 1.0f;

	init_buttons(window_width, window_height);

	while (!WindowShouldClose())
	{
		if (IsKeyPressed(KEY_ESCAPE))
		{
			CloseWindow();
		}

		if (IsKeyPressed(KEY_SPACE)) paused = !paused;

		if (IsKeyPressed(KEY_F1)) controls_open = !controls_open;

		if (IsKeyDown(KEY_LEFT_CONTROL))
		{
			if (IsKeyPressed(KEY_S))
			{
				try
				{
					Saver::save_state(camera);
				}
				catch (const NoSaveFileException& e) {}
				catch (const FileOpenFailedException& e)
				{
					show_warning("Could not open the file.");
				}
			}
			else if (IsKeyPressed(KEY_L))
			{
				paused = true;
				try
				{
					Saver::load_state(camera);
				}
				catch (const NoSaveFileException& e) {}
				catch (const FileOpenFailedException& e)
				{
					show_warning("Could not open the file.");
				}
				catch (const InvalidFileException& e)
				{
					show_warning("Selected file is not a valid save file.");
				}
			}
		}

		float current_speed = (_move_speed / camera.zoom) * GetFrameTime();

		for (auto& button : particle_buttons)
		{
			if (button.is_pressed()) selected_particle = button.get_particle_id();
		}

		check_spawns(camera);

		if (IsKeyDown(KEY_A)) camera.target.x -= current_speed;
		if (IsKeyDown(KEY_D)) camera.target.x += current_speed;
		if (IsKeyDown(KEY_W)) camera.target.y -= current_speed;
		if (IsKeyDown(KEY_S)) camera.target.y += current_speed;

		float wheel = GetMouseWheelMove();
		if (wheel != 0.0f)
		{
			Vector2 screen_center = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
			Vector2 world_center = GetScreenToWorld2D(screen_center, camera);

			camera.target = world_center;
			camera.zoom += wheel * _zoom_speed;

			if (camera.zoom <= 0.1f) camera.zoom = 0.1f;
		}

		BeginDrawing();
		ClearBackground(BLACK);
		
		BeginMode2D(camera);
		for (auto& particle : ParticleHandler::particles)
		{
			const Vector2& position = particle->get_position();
			DrawCircle((int)round(position.x), (int)round(position.y), particle->get_size(), particle->get_color());
		}
		EndMode2D();

		render_buttons();
		render_ui_text(window_width);
		if (controls_open) render_controls(window_width, window_height);
		render_warning(window_width, window_height);

		EndDrawing();

		if (can_simulate())
		{
			simulation_step();
		}
		else ParticleHandler::finalize_adds();
	}
}

void Simulation::simulation_step()
{
	auto& particles = ParticleHandler::particles;
	size_t particle_count = particles.size();
	bool use_parallel = particle_count > _parallel_threshold;

	#pragma warning(disable: 6993)
	#pragma omp parallel for if(use_parallel)
	for (size_t i = 0; i < particle_count; ++i)
	{
		particles[i]->step(particles);
	}

	#pragma omp parallel for if(use_parallel)
	for (size_t i = 0; i < particle_count; ++i)
	{
		particles[i]->update_position();
	}

	#pragma omp parallel for if(use_parallel)
	for (size_t i = 0; i < particle_count; ++i)
	{
		particles[i]->check_collisions(particles);
	}

	#pragma omp parallel for if(use_parallel)
	for (size_t i = 0; i < particle_count; ++i)
	{
		particles[i]->update_position();
	}

	ParticleHandler::finalize_adds();
	ParticleHandler::finalize_removes();
}

void Simulation::init_buttons(int window_width, int window_height)
{
	const auto& particle_registry = Particle::get_registry();
	const int particle_type_count = (int)particle_registry.size();

	const float button_width_total = ((float)window_width - _button_spacing) / particle_type_count;
	const float button_width = (float)button_width_total - _button_spacing;
	const float button_height = window_height / 20.0f;
	
	const float button_pos_y = window_height - button_height - _button_padding_bottom;
	for (int i = 0; i < particle_type_count; ++i)
	{
		const float button_pos_x = _button_spacing + (button_width_total * i);
		Rectangle bounds = { button_pos_x, button_pos_y, button_width, button_height };
		particle_buttons.push_back(Button(i, bounds, particle_registry[i].type_name,
			_button_font_size, _button_font_color, _button_base_color, _button_hover_color,
			_button_press_color));
	}
}

void Simulation::render_buttons()
{
	for (auto& button : particle_buttons)
	{
		button.draw();
	}
}

void Simulation::render_ui_text(int window_width)
{
	string count = format("Total Particles: {}", ParticleHandler::particles.size());
	int text_x = _ui_text_padding;
	int text_y = _ui_text_padding;
	DrawText(count.c_str(), text_x, text_y, _ui_font_size, _ui_font_color);

	string particle = "Selected: " + Particle::get_registry()[selected_particle].type_name;
	text_x = _ui_text_padding;
	text_y += _ui_font_size + _ui_text_padding;
	DrawText(particle.c_str(), text_x, text_y, _ui_font_size, _ui_font_color);

	string help = "F1 - Help";
	int text_width = MeasureText(help.c_str(), _ui_font_size);
	text_x = window_width - text_width - _ui_text_padding;
	text_y = _ui_text_padding;
	DrawText(help.c_str(), text_x, text_y, _ui_font_size, _ui_font_color);

	if (paused)
	{
		string pause = "Paused";
		text_width = MeasureText(pause.c_str(), _ui_font_size);
		text_x = window_width - text_width - _ui_text_padding;
		text_y += _ui_font_size + _ui_text_padding;
		DrawText(pause.c_str(), text_x, text_y, _ui_font_size, _ui_font_color);
	}
}

void Simulation::render_controls(int window_width, int window_height)
{
	int max_width = 0;
	for (auto& control : controls)
	{
		max_width = max(max_width, MeasureText(control.c_str(), _ui_font_size));
	}
	max_width += 2 * _ui_text_padding;

	float total_text_height = (float)controls.size() * (_ui_font_size + _ui_text_padding) + _ui_text_padding;
	float background_x = (window_width - max_width) / 2.0f;
	float background_y = (window_height - total_text_height) / 2.0f;
	Rectangle background{ background_x, background_y, (float)max_width, total_text_height };
	DrawRectangleRounded(background, _controls_background_roundness, _background_segments, _controls_background_color);

	int text_x;
	int text_y = (int)background_y + _ui_text_padding;
	for (auto& control : controls)
	{
		text_x = (window_width - MeasureText(control.c_str(), _ui_font_size)) / 2;
		DrawText(control.c_str(), text_x, text_y, _ui_font_size, _ui_font_color);
		text_y += _ui_font_size + _ui_text_padding;
	}
}

void Simulation::show_warning(string warning)
{
	warning_text = warning;
	warning_timer = 0.0f;
	warning_skip_frames = 0;
}

void Simulation::render_warning(int window_width, int window_height)
{
	if (warning_timer < _warning_time)
	{
		if (warning_skip_frames < 2)
		{
			++warning_skip_frames;
			return;
		}

		warning_timer += GetFrameTime();
		int text_width = MeasureText(warning_text.c_str(), _ui_font_size);
		int text_x = (window_width - text_width) / 2;
		int text_y = (window_height - _ui_font_size) / 2;

		Rectangle background{ (float)text_x - _ui_text_padding, (float)text_y - _ui_text_padding,
			text_width + 2.0f * _ui_text_padding, _ui_font_size + 2.0f * _ui_text_padding };
		DrawRectangleRounded(background, _warning_background_roundness, _background_segments, _warning_background_color);

		DrawText(warning_text.c_str(), text_x, text_y, _ui_font_size, _ui_font_color);
	}
}

bool Simulation::any_button_hovered()
{
	for (auto& button : particle_buttons)
	{
		if (button.get_is_hovered()) return true;
	}
	return false;
}

bool Simulation::any_particle_hovered(Camera2D& camera)
{
	auto mouse_pos = GetScreenToWorld2D(GetMousePosition(), camera);
	for (auto& particle : ParticleHandler::particles)
	{
		if (CheckCollisionPointCircle(mouse_pos, particle->get_position(), particle->get_size())) return true;
	}
	return false;
}

void Simulation::check_spawns(Camera2D& camera)
{
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !any_button_hovered() && !any_particle_hovered(camera) && !controls_open)
	{
		if (can_spawn)
		{
			can_spawn = false;
			spawn_particle(camera);
		}
		else spawn_timer += GetFrameTime();

		if (spawn_timer >= _spawn_interval)
		{
			can_spawn = true;
			spawn_timer = 0.0f;
		}
	}
	else if (!IsMouseButtonDown(MOUSE_LEFT_BUTTON) || controls_open)
	{
		can_spawn = true;
		spawn_timer = 0.0f;
	}
}

void Simulation::spawn_particle(Camera2D& camera)
{
	Vector2 spawn_pos = GetScreenToWorld2D(GetMousePosition(), camera);
	auto& factory = Particle::get_registry()[selected_particle].create;
	ParticleHandler::add_particle(factory(spawn_pos));
}