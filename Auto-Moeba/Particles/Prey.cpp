#include "Prey.h"

int Prey::_current_food = 0;

void Prey::collide(const vector<shared_ptr<Particle>>& collisions)
{
	for (auto& particle : collisions)
	{
		if (particle->is_type(ParticleType::Predator))
		{
			ParticleHandler::remove_particle(this);
			break;
		}
		else if (particle->is_type(ParticleType::Food))
		{
			_current_food++;
			if (_current_food >= _food_to_reproduce)
			{
				_current_food = 0;
				ParticleHandler::add_particle(make_shared<Prey>(particle->get_position()));
			}
		}
	}
}

float Prey::scale_attraction(float attraction, const shared_ptr<const Particle>& other, const RelativePosition& rel_pos) const
{
	if (other->is_type(ParticleType::Prey))
	{
		return rel_pos.dist < _group_dist ? -attraction : attraction;
	}
	return attraction;
}