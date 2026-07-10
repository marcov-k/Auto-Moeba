#include "Utilities.h"

RelativePosition Utilities::relative_position(const Vector2& a, const Vector2& b)
{
	float x_dist = a.x - b.x;
	float y_dist = a.y - b.y;
	float dist = hypot(x_dist, y_dist);
	float angle = atan2(y_dist, x_dist);

	return RelativePosition{ x_dist, y_dist, dist, angle };
}