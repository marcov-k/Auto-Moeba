#include "Particle.h"
#include "Waste.h"
#include "Nutrients.h"

void Particle::check_collisions(const vector<shared_ptr<Particle>>& particles)
{
	vector<shared_ptr<Particle>> collisions;

	vector<Vector2> moves;

	for (const auto& particle : particles)
	{
		if (particle.get() == this) continue;

		const auto rel_pos = Utilities::relative_position(particle->get_position(), _position);

		const float min_dist = particle->get_size() + get_size();
		if (rel_pos.dist <= min_dist)
		{
			collisions.push_back(particle);

			const float correction = _collision_correction * (min_dist - rel_pos.dist);
			const auto dir = Utilities::unit_vector(rel_pos.offset);
			moves.push_back(Utilities::project_vector(-correction, dir));
		}
	}

	if (!moves.empty())
	{
		float move_count = (float)moves.size();
		Vector2 total_move = { 0.0f, 0.0f };
		for (const auto& move : moves)
		{
			total_move.x += move.x;
			total_move.y += move.y;
		}
		total_move.x /= move_count;
		total_move.y /= move_count;

		_next_position.x = _position.x + total_move.x;
		_next_position.y = _position.y + total_move.y;
	}

	collide(collisions);
}

void Particle::update_acceleration(const vector<shared_ptr<Particle>>& particles)
{
	_acceleration = { 0.0f, 0.0f };

	for (auto& particle : particles)
	{
		if (particle.get() == this) continue;

		const auto& attractions = particle->get_attractions();

		const auto rel_pos = Utilities::relative_position(particle->get_position(), _position);

		const float min_dist = particle->get_size() + get_size();
		if (rel_pos.dist > _effect_radius || rel_pos.dist < min_dist) continue;

		float attract = 0.0f;
		for (auto type : get_types())
		{
			attract += attractions.at(type);
		}

		attract = scale_attraction(attract, particle, rel_pos);
		const auto dir = Utilities::unit_vector(rel_pos.offset);
		const auto attract_vec = Utilities::project_vector(_attraction_scale * scale_attraction_by_dist(attract, rel_pos.dist), dir);
		_acceleration.x += attract_vec.x;
		_acceleration.y += attract_vec.y;
	}

	const auto dir = Utilities::unit_vector(_acceleration);
	float accel_mag = Utilities::vector_magnitude(_acceleration);
	accel_mag = min(accel_mag, _max_acceleration);
	_acceleration = Utilities::project_vector(accel_mag, dir);
}

void Particle::update_velocity()
{
	_velocity.x += _acceleration.x * _acceleration_scale * GetFrameTime();
	_velocity.y += _acceleration.y * _acceleration_scale * GetFrameTime();
	_velocity = Utilities::project_vector(1.0f - _velocity_decay * GetFrameTime(), _velocity);
}

void Particle::update_next_position()
{
	_next_position.x = _position.x + _velocity.x * GetFrameTime();
	_next_position.y = _position.y + _velocity.y * GetFrameTime();
}

float Particle::scale_attraction_by_dist(float attraction, float distance)
{
	return attraction / (distance * 2);
}

void Particle::step_general()
{
	float& health = get_health();
	health -= get_health_decay() * GetFrameTime();
	if (health <= 0.0f)
	{
		if (Utilities::generate_random() < 0.5f)
		{
			ParticleHandler::add_particle(make_shared<Waste>(_position));
		}
		else
		{
			ParticleHandler::add_particle(make_shared<Nutrients>(_position));
		}
		ParticleHandler::remove_particle(this);
	}
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
	const int type_count = static_cast<int>(ParticleType::End);

	if (get_types().size() < 1)
	{
		_attractions = TypeAttractions::get_attractions(ParticleType::End);
	}

	for (auto type : get_types())
	{
		auto atts = TypeAttractions::get_attractions(type);

		for (int i = 0; i < type_count; ++i)
		{
			auto add_type = static_cast<ParticleType>(i);
			_attractions[add_type] += atts[add_type];
		}
	}
}

void Particle::reproduce(const Vector2& start_position, Particle* parent,
	const function<shared_ptr<Particle>(const Vector2&)> factory)
{
	auto child = factory(start_position);
	child->generate_child_attractions(parent->get_attractions());
	ParticleHandler::add_particle(child);
}

void Particle::generate_child_attractions(const unordered_map<ParticleType, float>& parent_attractions)
{
	for (auto& attraction : parent_attractions)
	{
		_attractions[attraction.first] = attraction.second + Utilities::generate_random(-_mutation_range, _mutation_range);
	}
}