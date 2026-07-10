#include "Runner.h"

void Runner::generate_next_position(const vector<shared_ptr<Particle>>& particles)
{
	if (particles.size() <= 1) return;

	float closest_dist = numeric_limits<float>::max();
	shared_ptr<Particle> closest;
	for (auto& particle : particles)
	{
		if (particle.get() == this) continue;

		float dist = Utilities::dist(particle->get_position(), _position);
		if (dist < closest_dist)
		{
			closest_dist = dist;
			closest = particle;
		}
	}

	float x_dist = closest->get_position().x - _position.x;
	float y_dist = closest->get_position().y - _position.y;
	float angle = atan2(y_dist, x_dist);

	float move = _speed * GetFrameTime();
	float move_x = move * cos(angle);
	float move_y = move * sin(angle);

	_next_position.x = _position.x - move_x;
	_next_position.y = _position.y - move_y;
}