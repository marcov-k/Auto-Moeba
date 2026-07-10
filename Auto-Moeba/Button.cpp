#include "Button.h"

void Button::draw()
{
	Vector2 mouse_pos = GetMousePosition();
	_is_hovered = CheckCollisionPointRec(mouse_pos, _bounds);

	Color current_color;

	if (_is_hovered)
	{
		current_color = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? _press_color : _hover_color;
	}
	else current_color = _base_color;

	DrawRectangleRec(_bounds, current_color);
	DrawRectangleLinesEx(_bounds, 2.0f, DARKGRAY);

	int text_width = MeasureText(_text.c_str(), _font_size);
	int text_x = _bounds.x + (_bounds.width - text_width) / 2;
	int text_y = _bounds.y + (_bounds.height - _font_size) / 2;

	DrawText(_text.c_str(), text_x, text_y, _font_size, _font_color);
}

bool Button::is_pressed() const
{
	return _is_hovered && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
}