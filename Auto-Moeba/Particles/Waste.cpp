#include "Waste.h"

void Waste::collide(const vector<shared_ptr<Particle>>& collisions)
{
	for (auto& particle : collisions)
	{
		if (particle->is_type(ParticleType::Scavenger) && particle->can_eat())
		{
			ParticleHandler::remove_particle(this);
			break;
		}
	}
}