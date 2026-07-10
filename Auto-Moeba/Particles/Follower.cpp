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
			auto rel_pos = Utilities::relative_position(particle->get_position(), _position);
			bool follower = typeid(*particle.get()) == typeid(Follower);
			if (!follower && rel_pos.dist < _follow_range && rel_pos.dist < closest_dist)
			{
				closest_dist = rel_pos.dist;
				closest = particle;
			}
		}
		_target = closest;
		_target->add_ignore_target(shared_from_this());
	}
	else
	{
		auto rel_pos = Utilities::relative_position(_target->get_position(), _position);

		float move = _speed * GetFrameTime();
		float move_x = move * cos(rel_pos.angle);
		float move_y = move * sin(rel_pos.angle);

		if (rel_pos.dist < _follow_dist - _eps)
		{
			_next_position.x = _position.x - move_x;
			_next_position.y = _position.y - move_y;
		}
		else if (rel_pos.dist > _follow_dist + _eps)
		{
			_next_position.x = _position.x + move_x;
			_next_position.y = _position.y + move_y;
		}
	}
}