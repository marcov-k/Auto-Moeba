#include "Particle.h"

const vector<shared_ptr<Particle>> Particle::check_collisions(const vector<shared_ptr<Particle>>& particles)
{
	vector<shared_ptr<Particle>> collisions;

	for (const auto& particle : particles)
	{
		if (particle.get() == this) continue;

		float dist = Utilities::dist(particle->get_position(), _next_position);

		float min_dist = particle->get_size() + get_size();
		if (dist <= particle->get_size() + get_size())
		{
			collisions.push_back(particle);

			float x_dist = particle->get_position().x - _next_position.x;
			float y_dist = particle->get_position().y - _next_position.y;
			float angle = atan2(y_dist, x_dist);

			float correction = min_dist - dist;
			float corr_x = correction * cos(angle);
			float corr_y = correction * sin(angle);

			_next_position.x -= corr_x;
			_next_position.y -= corr_y;
		}
	}

	return collisions;
}