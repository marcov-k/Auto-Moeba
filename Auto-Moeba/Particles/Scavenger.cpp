#include "Scavenger.h"

int Scavenger::_current_waste = 0;

void Scavenger::collide(const vector<shared_ptr<Particle>>& collisions)
{
	for (auto& particle : collisions)
	{
		if (particle->is_type(ParticleType::Waste))
		{
			_current_waste++;
			if (_current_waste >= _waste_to_reproduce)
			{
				_current_waste = 0;
				ParticleHandler::add_particle(make_shared<Scavenger>(particle->get_position()));
			}
		}
	}
}

float Scavenger::scale_attraction(float attraction, const shared_ptr<const Particle>& other, const RelativePosition& rel_pos) const
{
	return attraction;
}