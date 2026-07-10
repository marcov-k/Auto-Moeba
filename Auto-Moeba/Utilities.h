#pragma once

#include <algorithm>
#include <cmath>

#include "raylib.h"

using namespace std;

struct RelativePosition
{
	Vector2 offset;
	float dist;
};

class Utilities
{
public:
	Utilities() = delete;

	// Computes the relative position data for position a in respect to position b.
	static RelativePosition relative_position(const Vector2& a, const Vector2& b);

	static Vector2 unit_vector(const Vector2& v);

	static Vector2 project_vector(float val, const Vector2& vec);

	static float vector_magnitude(const Vector2& v);
};