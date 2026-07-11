#include "Scavenger.h"
#include "Nutrients.h"

void Scavenger::collide(const vector<shared_ptr<Particle>>& collisions)
{
	for (auto& particle : collisions)
	{
		if (particle->is_type(ParticleType::Waste))
		{
			_health.value() = get_max_health();

			auto rel_pos = Utilities::relative_position(particle->get_position(), _position);
			auto reverse_pos = Utilities::project_vector(-1.0f, rel_pos.offset);
			auto nutrient_pos = Utilities::add_vector(reverse_pos, _position);
			ParticleHandler::add_particle(make_shared<Nutrients>(nutrient_pos));

			_current_waste++;
			if (_current_waste >= _waste_to_reproduce)
			{
				_current_waste = 0;
				ParticleHandler::add_particle(make_shared<Scavenger>(particle->get_position()));
			}
		}
	}
}

void Scavenger::step_specific(const vector<shared_ptr<Particle>>& particles)
{

}

float Scavenger::scale_attraction(float attraction, const shared_ptr<const Particle>& other, const RelativePosition& rel_pos) const
{
	return attraction;
}