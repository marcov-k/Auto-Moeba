#include "Follower.h"

void Follower::generate_next_position(const vector<shared_ptr<Particle>>& particles)
{
	if (particles.size() <= 1) return;

	if (_target == nullptr)
	{
		float closest_dist = numeric_limits<float>::max();
		shared_ptr<Particle> closest = nullptr;
		for (auto& particle : particles)
		{
			float dist = Utilities::dist(particle->get_position(), _position);
			bool follower = typeid(*particle.get()) == typeid(Follower);
			if (!follower && dist < _follow_range && dist < closest_dist)
			{
				closest_dist = dist;
				closest = particle;
			}
		}
		_target = closest;
	}
	else
	{
		float x_dist = _target->get_position().x - _position.x;
		float y_dist = _target->get_position().y - _position.y;
		float dist = hypot(x_dist, y_dist);
		float angle = atan2(y_dist, x_dist);

		float move = _speed * GetFrameTime();
		float move_x = move * cos(angle);
		float move_y = move * sin(angle);

		if (dist < _follow_dist - _eps)
		{
			_next_position.x = _position.x - move_x;
			_next_position.y = _position.y - move_y;
		}
		else if (dist > _follow_dist + _eps)
		{
			_next_position.x = _position.x + move_x;
			_next_position.y = _position.y + move_y;
		}
	}
}