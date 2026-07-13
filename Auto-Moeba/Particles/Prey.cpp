#include "Prey.h"

void Prey::collide(const vector<shared_ptr<Particle>>& collisions)
{
	for (auto& particle : collisions)
	{
		if (particle->is_type(ParticleType::Predator) && particle->can_eat())
		{
			ParticleHandler::remove_particle(this);
			break;
		}
		else if (particle->is_type(ParticleType::Food) && can_eat())
		{
			_ate = true;

			_current_food++;
			if (_current_food >= _food_to_reproduce)
			{
				_current_food = 0;
				reproduce(particle->get_position(), this, [](const Vector2& start_pos) -> shared_ptr<Particle>
					{
						return make_shared<Prey>(start_pos);
					});
			}
		}
	}
}

float Prey::scale_attraction(float attraction, const shared_ptr<const Particle>& other, const RelativePosition& rel_pos)
{
	if (other->is_type(ParticleType::Food))
	{
		return attraction * _hunger_scaling * (1.0f - get_health_percent());
	}
	if (other->is_type(ParticleType::Prey))
	{
		return rel_pos.dist < _group_dist_mult * (other->get_size() + get_size()) ? -attraction : attraction;
	}
	return attraction;
}

bool Prey::ignore_attraction(const shared_ptr<const Particle>& other, const RelativePosition& rel_pos) const
{
	if (other->is_type(ParticleType::Prey))
	{
		return rel_pos.dist < _group_dist_mult * (other->get_size() + get_size());
	}
	return false;
}

void Prey::write_unique_data(ofstream& stream) const
{
	FileUtils::write_int32(stream, _current_food);
}

void Prey::read_unique_data(ifstream& stream)
{
	_current_food = FileUtils::read_int32(stream);
}