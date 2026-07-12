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

float Connector::scale_attraction(float attraction, const shared_ptr<const Particle>& other, const RelativePosition& rel_pos)
{
	if (other->is_type(ParticleType::Food))
	{
		return can_eat() ? attraction : 0.25f * attraction;
	}
	else if (!other->is_type(ParticleType::Waste))
	{
		return rel_pos.dist < _min_dist_mult * (other->get_size() + get_size()) ? -attraction : attraction;
	}
	return attraction;
}