#include "Predator.h"
#include "Waste.h"

void Predator::collide(const vector<shared_ptr<Particle>>& collisions)
{
	for (auto& particle : collisions)
	{
		if (particle->is_type(ParticleType::Prey))
		{
			_health.value() = get_max_health();

			auto rel_pos = Utilities::relative_position(particle->get_position(), _position);
			auto reverse_pos = Utilities::project_vector(-1.0f, rel_pos.offset);
			auto waste_pos = Utilities::add_vector(reverse_pos, _position);
			ParticleHandler::add_particle(make_shared<Waste>(waste_pos));

			_current_prey++;
			if (_current_prey >= _prey_to_reproduce)
			{
				_current_prey = 0;
				reproduce(particle->get_position(), this, [](const Vector2& start_pos) -> shared_ptr<Particle>
					{
						return make_shared<Predator>(start_pos);
					});
			}
		}
	}
}