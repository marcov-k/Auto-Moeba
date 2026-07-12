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
				reproduce(particle->get_position(), this, [](const Vector2& start_pos) -> shared_ptr<Particle>
					{
						return make_shared<Scavenger>(start_pos);
					});
			}
		}
	}
}