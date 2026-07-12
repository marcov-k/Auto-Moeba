#include "Utilities.h"

RelativePosition Utilities::relative_position(const Vector2& a, const Vector2& b)
{
	float x_dist = a.x - b.x;
	float y_dist = a.y - b.y;
	float dist = hypot(x_dist, y_dist);

	return RelativePosition{ Vector2{ x_dist, y_dist }, dist };
}

Vector2 Utilities::add_vector(const Vector2& a, const Vector2& b)
{
	return Vector2{ a.x + b.x, a.y + b.y };
}

Vector2 Utilities::sub_vector(const Vector2& a, const Vector2& b)
{
	return Vector2{ a.x - b.x, a.y - b.y };
}

Vector2 Utilities::unit_vector(const Vector2& v)
{
	float mag = hypot(v.x, v.y);
	return mag < 1e-4f ? Vector2{ 0.0f, 0.0f } : Vector2{v.x / mag, v.y / mag};
}

Vector2 Utilities::project_vector(float val, const Vector2& vec)
{
	float x = vec.x * val;
	float y = vec.y * val;
	return Vector2{ x, y };
}

float Utilities::vector_magnitude(const Vector2& v)
{
	return hypot(v.x, v.y);
}

float Utilities::vector_dot(const Vector2& a, const Vector2& b)
{
	return a.x * b.x + a.y * b.y;
}