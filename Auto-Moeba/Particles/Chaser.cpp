#include "Chaser.h"
#include "Follower.h"
#include "Sticker.h"

void Chaser::generate_next_position(const vector<shared_ptr<Particle>>& particles)
{
	if (particles.size() <= 1) return;

	float closest_dist = numeric_limits<float>::max();
	bool closest_chaser = false;
	shared_ptr<Particle> closest = nullptr;

	for (auto& particle : particles)
	{
		if (ignore_target(particle.get())) continue;

		auto rel_pos = Utilities::relative_position(particle->get_position(), _position);

		bool chaser = typeid(*particle.get()) == typeid(Chaser);
		if (!chaser)
		{
			if (closest_chaser || rel_pos.dist < closest_dist)
			{
				closest_dist = rel_pos.dist;
				closest_chaser = false;
				closest = particle;
			}
		}
		else
		{
			if ((closest_chaser && rel_pos.dist < closest_dist) || closest == nullptr)
			{
				closest_dist = rel_pos.dist;
				closest_chaser = true;
				closest = particle;
			}
		}
	}

	if (closest != nullptr)
	{
		auto rel_pos = Utilities::relative_position(closest->get_position(), _position);

		float move = _speed * GetFrameTime();
		float move_x = move * cos(rel_pos.angle);
		float move_y = move * sin(rel_pos.angle);

		_next_position.x = _position.x + move_x;
		_next_position.y = _position.y + move_y;
	}
}