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

void Nutrients::write_unique_data(ofstream& stream) const
{
	FileUtils::write_float(stream, _current_growth);
}

void Nutrients::read_unique_data(ifstream& stream)
{
	_current_growth = FileUtils::read_float(stream);
}