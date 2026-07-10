#include "Sticker.h"

void Sticker::collide()
{
	if (_collisions.size() > 0)
	{
		for (auto& collision : _collisions)
		{
			if (collision.get() != _stuck_to.get())
			{
				_stuck_to = collision;
				_stuck_to->add_ignore_collision(shared_from_this());
				_stuck_to->add_ignore_target(shared_from_this());

				auto rel_pos = Utilities::relative_position(_position, _stuck_to->get_position());
				_stuck_offset = { rel_pos.x_dist, rel_pos.y_dist };
				break;
			}
		}
	}
}

void Sticker::generate_next_position(const vector<shared_ptr<Particle>>& particles)
{
	if (_stuck_to != nullptr)
	{
		_next_position.x = _stuck_to->get_position().x + _stuck_offset.x;
		_next_position.y = _stuck_to->get_position().y + _stuck_offset.y;
	}
}