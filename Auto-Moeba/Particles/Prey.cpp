#include "Prey.h"

void Prey::collide(const vector<shared_ptr<Particle>>& collisions)
{
	for (auto& particle : collisions)
	{
		if (particle->is_type(ParticleType::Predator)) ParticleHandler::remove_particle(this);
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