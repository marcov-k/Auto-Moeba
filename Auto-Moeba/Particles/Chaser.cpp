#include "Chaser.h"

void Chaser::generate_next_position(const vector<shared_ptr<Particle>>& particles)
{
	if (particles.size() <= 1) return;

	float closest_dist = numeric_limits<float>::max();
	bool closest_chaser = false;
	shared_ptr<Particle> closest;

	for (auto& particle : particles)
	{
		if (particle.get() == this) continue;

		float dist = Utilities::dist(particle->get_position(), _position);
		bool chaser = typeid(particle.get()) == typeid(Chaser);
		if (!chaser || dist < closest_dist)
		{
			if (!chaser || closest_chaser)
			{
				closest_dist = dist;
				closest_chaser = chaser;
				closest = particle;
			}
		}
	}

	float x_dist = closest->get_position().x - _position.x;
	float y_dist = closest->get_position().y - _position.y;
	float angle = atan2(y_dist, x_dist);

	float move = _speed * GetFrameTime();
	float move_x = move * cos(angle);
	float move_y = move * sin(angle);

	_next_position.x = _position.x + move_x;
	_next_position.y = _position.y + move_y;
}