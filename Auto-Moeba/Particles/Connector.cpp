#include "Connector.h"
#include "Anchor.h"

void Connector::collide(const vector<shared_ptr<Particle>>& collisions)
{
	if (!can_eat()) return;

	for (auto& particle : collisions)
	{
		if (particle.get() == this) continue;

		if (particle->is_type(ParticleType::Food))
		{
			_health.value() = get_max_health();

			_current_food++;
			if (_current_food >= _food_to_reproduce)
			{
				_current_food = 0;
				if (Utilities::generate_random() < 0.1f)
				{
					ParticleHandler::add_particle(make_shared<Anchor>(particle->get_position()));
				}
				else
				{
					reproduce(particle->get_position(), this, [](const Vector2& start_pos) -> shared_ptr<Particle>
						{
							return make_shared<Connector>(start_pos);
						});
				}
			}
		}
	}
}