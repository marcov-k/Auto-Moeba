#include "Auto-Moeba.h"
#include "raylib.h"

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
bool Simulation::can_spawn = true;
float Simulation::spawn_timer = 0.0f;

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

		EndDrawing();

		if (!paused)
		{
			simulation_step();
		}
		else ParticleHandler::finalize_adds();
	}
}

void Simulation::simulation_step()
{
	// Can be made parallel
	for (auto& particle : ParticleHandler::particles)
	{
		particle->step(ParticleHandler::particles);
	}

	// Can be made parallel
	for (auto& particle : ParticleHandler::particles)
	{
		particle->update_position();
	}

	// Can be made parallel
	for (auto& particle : ParticleHandler::particles)
	{
		particle->check_collisions(ParticleHandler::particles);
	}

	// Can be made parallel
	for (auto& particle : ParticleHandler::particles)
	{
		particle->update_position();
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
	
	const float button_pos_y = window_height - button_height;
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
	string particle = "Selected: " + Particle::get_registry()[selected_particle].type_name;
	DrawText(particle.c_str(), _ui_text_padding, _ui_text_padding, _ui_font_size, _ui_font_color);

	if (paused)
	{
		string pause_text = "Paused";
		int text_width = MeasureText(pause_text.c_str(), _ui_font_size);
		int text_x = window_width - text_width - _ui_text_padding;
		DrawText(pause_text.c_str(), text_x, _ui_text_padding, _ui_font_size, _ui_font_color);
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
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !any_button_hovered() && !any_particle_hovered(camera))
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
	else if (!IsMouseButtonDown(MOUSE_LEFT_BUTTON))
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