#include "Particle.h"

void Particle::check_collisions(const vector<shared_ptr<Particle>>& particles)
{
	vector<shared_ptr<Particle>> collisions;

	Vector2 adjusted_pos = _position;

	for (const auto& particle : particles)
	{
		if (particle.get() == this) continue;

		auto rel_pos = Utilities::relative_position(particle->get_position(), _position);

		float min_dist = particle->get_size() + get_size();
		if (rel_pos.dist <= min_dist)
		{
			collisions.push_back(particle);

			float correction = min_dist - rel_pos.dist;
			auto dir = Utilities::unit_vector(rel_pos.offset);
			auto corr_vec = Utilities::project_vector(correction, dir);

			adjusted_pos.x -= corr_vec.x;
			adjusted_pos.y -= corr_vec.y;
		}
	}
	_next_position = adjusted_pos;

	collide(collisions);
}

void Particle::generate_next_position(const vector<shared_ptr<Particle>>& particles)
{
	Vector2 attraction{ 0.0f, 0.0f };

	for (auto& particle : particles)
	{
		if (particle.get() == this) continue;

		const auto& attractions = particle->get_attractions();

		auto rel_pos = Utilities::relative_position(particle->get_position(), _position);

		if (rel_pos.dist < _effect_radius)
		{
			float attract = 0.0f;
			for (auto type : particle->get_types())
			{
				attract += attractions.at(type);
			}

			attract = scale_attraction(attract, particle, rel_pos);
			auto scale_vec = Utilities::project_vector(1.0f / rel_pos.dist, rel_pos.offset);
			auto attract_vec = Utilities::project_vector(attract * _attraction_scale, scale_vec);
			attraction.x += attract_vec.x;
			attraction.y += attract_vec.y;
		}
	}

	auto dir = Utilities::unit_vector(attraction);
	float attract_mag = Utilities::vector_magnitude(attraction);
	attract_mag = min(attract_mag, _max_attraction);

	auto move = Utilities::project_vector(attract_mag, dir);

	_next_position.x = _position.x + move.x * GetFrameTime();
	_next_position.y = _position.y + move.y * GetFrameTime();
}

bool Particle::is_type(ParticleType type) const
{
	auto types = get_types();
	for (size_t i = 0; i < types.size(); ++i)
	{
		if (types[i] == type) return true;
	}
	return false;
}

void Particle::generate_type_attractions()
{
	for (auto type : get_types())
	{
		auto atts = TypeAttractions::get_attractions(type);

		for (int i = 0; i < static_cast<int>(ParticleType::End); ++i)
		{
			auto add_type = static_cast<ParticleType>(i);
			_attractions[add_type] += atts[add_type];
		}
	}
}