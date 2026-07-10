#pragma once

#include <cmath>

#include "raylib.h"

class Utilities
{
public:
	Utilities() = delete;

	static float dist(const Vector2& a, const Vector2& b);
};