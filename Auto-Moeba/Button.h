#pragma once

#include <string>

#include "raylib.h"

using namespace std;

class Button
{
public:
	Button(int particle_id, Rectangle bounds, string text, int font_size, Color font_color, Color base_color,
		Color hover_color, Color press_color) : _particle_id(particle_id), _bounds(bounds), _text(text),
		_font_size(font_size), _font_color(font_color), _base_color(base_color), _hover_color(hover_color),
		_press_color(press_color) {}

	int get_particle_id() const
	{
		return _particle_id;
	}

	bool get_is_hovered() const
	{
		return _is_hovered;
	}

	void draw();

	bool is_pressed() const;

private:
	int _particle_id;
	Rectangle _bounds;
	string _text;
	int _font_size;
	Color _font_color;
	Color _base_color;
	Color _hover_color;
	Color _press_color;
	bool _is_hovered = false;
};