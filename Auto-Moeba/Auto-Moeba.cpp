#include "Auto-Moeba.h"
#include "raylib.h"

int main()
{
	const int width = 1850;
	const int height = 900;

	InitWindow(width, height, "Auto-Moeba");
	SetTargetFPS(60);

	Simulation::render_loop(width, height);
}

vector<shared_ptr<Particle>> Simulation::particles;
vector<Button> Simulation::particle_buttons;
int Simulation::selected_particle = 0;
bool Simulation::paused = true;

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

		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && !any_button_hovered())
		{
			spawn_particle(camera);
		}

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
		for (auto& particle : particles)
		{
			const Vector2& position = particle->get_position();
			DrawCircle(position.x, position.y, particle->get_size(), particle->get_color());
		}
		EndMode2D();

		render_buttons();
		render_ui_text(window_width);

		EndDrawing();

		if (!paused)
		{
			// Can be made parallel
			for (auto& particle : particles)
			{
				particle->step(particles);
			}

			// Must be kept sequential
			for (auto& particle : particles)
			{
				particle->collide();
			}

			// Can be made parallel
			for (auto& particle : particles)
			{
				particle->update_position();
			}
		}
	}
}

void Simulation::init_buttons(int window_width, int window_height)
{
	const auto& particle_registry = Particle::get_registry();
	const int particle_type_count = (int)particle_registry.size();

	const int button_width_total = (window_width - _button_spacing) / particle_type_count;
	const int button_width = button_width_total - _button_spacing;
	const int button_height = window_height / 20;
	
	const int button_pos_y = window_height - button_height;
	for (int i = 0; i < particle_type_count; ++i)
	{
		const int button_pos_x = _button_spacing + (button_width_total * i);
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

void Simulation::spawn_particle(Camera2D& camera)
{
	Vector2 spawn_pos = GetScreenToWorld2D(GetMousePosition(), camera);
	auto& factory = Particle::get_registry()[selected_particle].create;

	particles.push_back(factory(spawn_pos));
}
