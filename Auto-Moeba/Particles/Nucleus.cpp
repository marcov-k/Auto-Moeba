#include "Nucleus.h"

void Nucleus::collide(const vector<shared_ptr<Particle>>& collisions)
{
	for (auto& particle : collisions)
	{
		if (particle.get() == this) continue;

		if (particle->is_type(ParticleType::Predator) && particle->can_eat())
		{
			ParticleHandler::remove_particle(this);
			break;
		}
		else if (particle->is_type(ParticleType::Food) && can_eat())
		{
			_health.value() = get_max_health();

			_current_food++;
			if (_current_food >= _food_to_reproduce)
			{
				_current_food = 0;
				reproduce(particle->get_position(), this, [](const Vector2& start_pos) -> shared_ptr<Particle>
					{
						return make_shared<Nucleus>(start_pos);
					});
			}
		}
	}
}