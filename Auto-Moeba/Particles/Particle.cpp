#include "Particle.h"
#include "Sticker.h"

const vector<shared_ptr<Particle>> Particle::check_collisions(const vector<shared_ptr<Particle>>& particles)
{
	vector<shared_ptr<Particle>> collisions;

	for (const auto& particle : particles)
	{
		if (ignore_collision(particle.get())) continue;

		auto rel_pos = Utilities::relative_position(particle->get_position(), _next_position);

		float min_dist = particle->get_size() + get_size();
		if (rel_pos.dist <= min_dist)
		{
			collisions.push_back(particle);

			float correction = min_dist - rel_pos.dist;
			float corr_x = correction * cos(rel_pos.angle);
			float corr_y = correction * sin(rel_pos.angle);

			_next_position.x -= corr_x;
			_next_position.y -= corr_y;
		}
	}

	return collisions;
}

void Particle::remove_ignore_collision(Particle* particle)
{
	for (size_t i = 0; i < _ignore_collisions.size(); ++i)
	{
		if (_ignore_collisions[i].get() == particle)
		{
			_ignore_collisions.erase(_ignore_collisions.begin() + i);
			break;
		}
	}
}

void Particle::remove_ignore_target(Particle* particle)
{
	for (size_t i = 0; i < _ignore_targets.size(); ++i)
	{
		if (_ignore_targets[i].get() == particle)
		{
			_ignore_targets.erase(_ignore_targets.begin() + i);
			break;
		}
	}
}

bool Particle::ignore_collision(Particle* particle)
{
	if (particle == this) return true;

	for (auto& collision : _ignore_collisions)
	{
		if (collision.get() == particle) return true;
	}
	return false;
}

bool Particle::ignore_target(Particle* particle)
{
	if (particle == this) return true;

	for (auto& target : _ignore_targets)
	{
		if (target.get() == particle) return true;
	}
	return false;
}