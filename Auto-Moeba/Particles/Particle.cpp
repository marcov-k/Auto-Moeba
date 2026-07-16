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

	vector<Vector2> zero_dirs;
	for (auto& particle : particles)
	{
		if (particle.get() == this) continue;

		const auto& attractions = particle->get_attractions();

		const auto rel_pos = Utilities::relative_position(particle->get_position(), _position);

		if (rel_pos.dist > _effect_radius) continue;

		const float min_dist = particle->get_size() + get_size();

		if (ignore_attraction(particle, rel_pos))
		{
			zero_dirs.push_back(Utilities::unit_vector(rel_pos.offset));
		}

		float attract = 0.0f;
		for (auto type : get_types())
		{
			attract += attractions.at(type);
		}

		attract = scale_attraction(attract, particle, rel_pos);
		const auto dir = Utilities::unit_vector(rel_pos.offset);
		const auto attract_vec = Utilities::project_vector(scale_attraction_by_dist(attract, rel_pos.dist), dir);
		_acceleration.x += attract_vec.x;
		_acceleration.y += attract_vec.y;
	}

	for (const auto& dir : zero_dirs)
	{
		float dot = Utilities::vector_dot(_acceleration, dir);
		Vector2 remove = Utilities::project_vector(dot, dir);
		_acceleration = Utilities::sub_vector(_acceleration, remove);
	}
}

void Particle::update_velocity()
{
	_velocity.x += _acceleration.x * _acceleration_scale * GetFrameTime();
	_velocity.y += _acceleration.y * _acceleration_scale * GetFrameTime();
	_velocity = Utilities::project_vector(1.0f - _velocity_decay * GetFrameTime(), _velocity);
}

void Particle::update_next_position()
{
	_next_position.x = _position.x + _velocity.x * _velocity_scale * GetFrameTime();
	_next_position.y = _position.y + _velocity.y * _velocity_scale * GetFrameTime();
}

float Particle::scale_attraction_by_dist(float attraction, float distance)
{
	return attraction / (distance / 4.0f);
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

bool Particle::ignore_attraction(const shared_ptr<const Particle>& other, const RelativePosition& rel_pos) const
{
	return rel_pos.dist < (other->get_size() + get_size());
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
	if (!_attractions.empty()) return;

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

void Particle::write_particle(ofstream& stream, unsigned short id)
{
	FileUtils::write_uint16(stream, id);
	FileUtils::write_vector2(stream, _position);

	FileUtils::write_size_t(stream, get_attractions().size());
	for (const auto& attraction : get_attractions())
	{
		FileUtils::write_int32(stream, static_cast<int>(attraction.first));
		FileUtils::write_float(stream, attraction.second);
	}

	FileUtils::write_float(stream, get_health());
	write_unique_data(stream);
}

auto Particle::get_factory(unsigned short id)
{
	for (const auto& reg : get_registry())
	{
		if (reg.id == id)
		{
			return reg.create;
		}
	}
	throw invalid_argument("Particle ID not registered.");
}

void Particle::create_from_data(ifstream& stream)
{
	auto id = FileUtils::read_uint16(stream);
	auto pos = FileUtils::read_vector2(stream);
	auto particle = get_factory(id)(pos);

	size_t attraction_count = FileUtils::read_size_t(stream);
	for (size_t i = 0; i < attraction_count; ++i)
	{
		int type = FileUtils::read_int32(stream);
		float attraction = FileUtils::read_float(stream);
		particle->_attractions[static_cast<ParticleType>(type)] = attraction;
	}

	particle->get_health() = FileUtils::read_float(stream);
	particle->read_unique_data(stream);
	ParticleHandler::add_particle(particle);
}