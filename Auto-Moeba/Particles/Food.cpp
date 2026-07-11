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

void Food::step_specific(const vector<shared_ptr<Particle>>& particles)
{

}

float Food::scale_attraction(float attraction, const shared_ptr<const Particle>& other, const RelativePosition& rel_pos) const
{
	return attraction;
}