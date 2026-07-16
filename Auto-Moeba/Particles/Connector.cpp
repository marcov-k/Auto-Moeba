#include "Connector.h"

void Connector::collide(const vector<shared_ptr<Particle>>& collisions)
{
	if (!can_eat()) return;

	for (auto& particle : collisions)
	{
		if (particle.get() == this) continue;

		if (particle->is_type(ParticleType::Food))
		{
			_ate = true;

			_current_food++;
			if (_current_food >= _food_to_reproduce)
			{
				_current_food = 0;
				reproduce(particle->get_position(), this, [](const Vector2& start_pos) -> shared_ptr<Particle>
					{
						return make_shared<Connector>(start_pos);
					});
			}
		}
	}
}

float Connector::scale_attraction(float attraction, const shared_ptr<const Particle>& other, const RelativePosition& rel_pos)
{
	if (other->is_type(ParticleType::Food))
	{
		return attraction * Utilities::exp_function(1.0f - get_health_percent(), _hunger_scaling);
	}
	else if (!other->is_type(ParticleType::Waste))
	{
		return rel_pos.dist < _min_dist_mult * (other->get_size() + get_size()) ? -attraction : attraction;
	}
	return attraction;
}

bool Connector::ignore_attraction(const shared_ptr<const Particle>& other, const RelativePosition& rel_pos) const
{
	if (!(other->is_type(ParticleType::Waste) || other->is_type(ParticleType::Food)))
	{
		return rel_pos.dist < _min_dist_mult * (other->get_size() + get_size());
	}
	return rel_pos.dist < (other->get_size() + get_size());
}

void Connector::write_unique_data(ofstream& stream) const
{
	FileUtils::write_int32(stream, _current_food);
}

void Connector::read_unique_data(ifstream& stream)
{
	_current_food = FileUtils::read_int32(stream);
}