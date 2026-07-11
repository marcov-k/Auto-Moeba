#include "Nutrients.h"
#include "Food.h"

void Nutrients::step_specific(const vector<shared_ptr<Particle>>& particles)
{
	_current_growth += GetFrameTime();
	if (_current_growth >= _growth_time)
	{
		ParticleHandler::add_particle(make_shared<Food>(_position));
		ParticleHandler::remove_particle(this);
	}
}