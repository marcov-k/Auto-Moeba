#pragma once

#include <cmath>

#include "raylib.h"

using namespace std;

struct RelativePosition
{
	float x_dist;
	float y_dist;
	float dist;
	float angle;
};

class Utilities
{
public:
	Utilities() = delete;

	// Computes the relative position data for position a in respect to position b.
	static RelativePosition relative_position(const Vector2& a, const Vector2& b);
};