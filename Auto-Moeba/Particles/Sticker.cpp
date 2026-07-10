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
				float x_dist = _position.x - _stuck_to->get_position().x;
				float y_dist = _position.y - _stuck_to->get_position().y;
				_stuck_offset = { x_dist, y_dist };
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