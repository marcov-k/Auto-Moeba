#include "Food.h"

void Food::collide(const vector<shared_ptr<Particle>>& collisions)
{
	for (auto& particle : collisions)
	{
		if (particle->is_type(ParticleType::Prey) || particle->is_type(ParticleType::Membrane) || particle->is_type(ParticleType::Nucleus)
			|| particle->is_type(ParticleType::Connector))
		{
			ParticleHandler::remove_particle(this);
			break;
		}
	}
}