#include "Waste.h"

void Waste::collide(const vector<shared_ptr<Particle>>& collisions)
{
	for (auto& particle : collisions)
	{
		if (particle->is_type(ParticleType::Scavenger))
		{
			ParticleHandler::remove_particle(this);
			break;
		}
	}
}

void Waste::step_specific(const vector<shared_ptr<Particle>>& particles)
{

}

float Waste::scale_attraction(float attraction, const shared_ptr<const Particle>& other, const RelativePosition& rel_pos) const
{
	return attraction;
}