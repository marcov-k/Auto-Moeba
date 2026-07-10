#pragma once

#include <cmath>
#include <functional>
#include <memory>
#include <vector>

#include "Particles.h"
#include "Button.h"

using namespace std;

struct Simulation
{
	static inline constexpr int _target_fps = 120;

	static inline constexpr float _zoom_speed = 0.05f;
	static inline constexpr float _move_speed = 500.0f;

	static inline constexpr int _ui_font_size = 30;
	static inline constexpr int _ui_text_padding = 25;
	static inline constexpr Color _ui_font_color = WHITE;

	static inline constexpr int _button_font_size = 20;
	static inline constexpr Color _button_font_color = BLACK;
	static inline constexpr Color _button_base_color = YELLOW;
	static inline constexpr Color _button_hover_color = GOLD;
	static inline constexpr Color _button_press_color = BROWN;
	static inline constexpr int _button_spacing = 25;

	static vector<shared_ptr<Particle>> particles;
	static vector<Button> particle_buttons;
	static int selected_particle;
	static bool paused;

	Simulation() = delete;

	static void render_loop(int window_width, int window_height);

	static void init_buttons(int window_width, int window_height);

	static void render_buttons();

	static void render_ui_text(int window_width);

	static bool any_button_hovered();

	static void spawn_particle(Camera2D& camera);
};