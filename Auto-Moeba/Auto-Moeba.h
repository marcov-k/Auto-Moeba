#pragma once

#include <cmath>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "raylib.h"

using namespace std;

class Button;

struct Simulation
{
	static inline constexpr int _target_fps = 120;
	static inline constexpr size_t _parallel_threshold = 400; // number of particles to parallelize at

	static inline constexpr float _spawn_interval = 0.02f;

	static inline constexpr float _zoom_speed = 0.05f;
	static inline constexpr float _move_speed = 500.0f;

	static inline constexpr int _ui_font_size = 30;
	static inline constexpr int _ui_text_padding = 25;
	static inline constexpr Color _ui_font_color = WHITE;
	static inline constexpr float _warning_time = 1.5f;

	static inline constexpr int _button_font_size = 20;
	static inline constexpr Color _button_font_color = BLACK;
	static inline constexpr Color _button_base_color = YELLOW;
	static inline constexpr Color _button_hover_color = GOLD;
	static inline constexpr Color _button_press_color = BROWN;
	static inline constexpr int _button_spacing = 15;
	static inline constexpr int _button_padding_bottom = 10;

	static inline constexpr int _background_segments = 30;

	static inline constexpr float _warning_background_roundness = 0.35f;
	static inline constexpr Color _warning_background_color = MAROON;

	static inline constexpr float _controls_background_roundness = 0.2f;
	static inline constexpr Color _controls_background_color = DARKPURPLE;
	static inline const vector<string> controls
	{
		"WASD - Move Camera",
		"Scroll - Zoom Camera",
		"LMB - Spawn Particle",
		"Space - Pause",
		"Ctrl + S - Save State",
		"Ctrl + L - Load State",
		"ESC - Quit"
	};

	static vector<Button> particle_buttons;
	static int selected_particle;
	static bool paused;
	static bool controls_open;
	static bool can_spawn;
	static float spawn_timer;
	static float warning_timer;
	static int warning_skip_frames;
	static string warning_text;

	Simulation() = delete;

	static void render_loop(int window_width, int window_height);

	static void simulation_step();

	static void init_buttons(int window_width, int window_height);

	static void render_buttons();

	static void render_ui_text(int window_width);

	static void render_controls(int window_width, int window_height);

	static void show_warning(string warning_text);

	static void render_warning(int window_width, int window_height);

	static bool any_button_hovered();

	static bool any_particle_hovered(Camera2D& camera);

	static bool can_simulate()
	{
		return !paused && !controls_open;
	}

	static void check_spawns(Camera2D& camera);

	static void spawn_particle(Camera2D& camera);
};