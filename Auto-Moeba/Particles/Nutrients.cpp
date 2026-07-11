#include "Nutrients.h"
#include "Food.h"

void Nutrients::collide(const vector<shared_ptr<Particle>>& collisions)
{

}

void Nutrients::step_specific(const vector<shared_ptr<Particle>>& particles)
{
	_current_growth += GetFrameTime();
	if (_current_growth >= _growth_time)
	{
		ParticleHandler::add_particle(make_shared<Food>(_position));
		ParticleHandler::remove_particle(this);
	}
}

float Nutrients::scale_attraction(float attraction, const shared_ptr<const Particle>& other, const RelativePosition& rel_pos) const
{
	return attraction;
}