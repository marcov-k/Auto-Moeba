#include "Predator.h"
#include "Waste.h"

void Predator::collide(const vector<shared_ptr<Particle>>& collisions)
{
	if (!can_eat()) return;

	for (auto& particle : collisions)
	{
		if (particle->is_type(ParticleType::Prey) || particle->is_type(ParticleType::Membrane) ||
			particle->is_type(ParticleType::Nucleus))
		{
			_ate = true;

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

float Predator::scale_attraction(float attraction, const shared_ptr<const Particle>& other, const RelativePosition& rel_pos)
{
	if (other->is_type(ParticleType::Prey) || other->is_type(ParticleType::Membrane) || other->is_type(ParticleType::Nucleus))
	{
		return attraction * _hunger_scaling * (1.0f - get_health_percent());
	}
	return attraction;
}

void Predator::write_unique_data(ofstream& stream) const
{
	FileUtils::write_int32(stream, _current_prey);
}

void Predator::read_unique_data(ifstream& stream)
{
	_current_prey = FileUtils::read_int32(stream);
}