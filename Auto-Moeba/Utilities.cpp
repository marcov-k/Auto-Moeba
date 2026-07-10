#include "Utilities.h"

using namespace std;

float Utilities::dist(const Vector2& a, const Vector2& b)
{
	return hypot(a.x - b.x, a.y - b.y);
}