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
		if (particle.get() == this) continue;

		if (Sticker* sticker = dynamic_cast<Sticker*>(particle.get()))
		{
			if (sticker->get_stuck_to().get() == this) continue;
		}

		float dist = Utilities::dist(particle->get_position(), _position);
		bool chaser = typeid(*particle.get()) == typeid(Chaser);
		
		if (!chaser)
		{
			if (closest_chaser || dist < closest_dist)
			{
				closest_dist = dist;
				closest_chaser = false;
				closest = particle;
			}
		}
		else
		{
			if ((closest_chaser && dist < closest_dist) || closest == nullptr)
			{
				closest_dist = dist;
				closest_chaser = true;
				closest = particle;
			}
		}
	}

	if (closest != nullptr)
	{
		float x_dist = closest->get_position().x - _position.x;
		float y_dist = closest->get_position().y - _position.y;
		float angle = atan2(y_dist, x_dist);

		float move = _speed * GetFrameTime();
		float move_x = move * cos(angle);
		float move_y = move * sin(angle);

		_next_position.x = _position.x + move_x;
		_next_position.y = _position.y + move_y;
	}
}