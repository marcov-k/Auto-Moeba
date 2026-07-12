#pragma once

#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <optional>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>

#include "raylib.h"
#include "../Utilities.h"
#include "TypeAttractions.h"
#include "../ParticleHandler.h"

using namespace std;

class Particle : public enable_shared_from_this<Particle>
{
public:
	Particle() {}

	Particle(const Vector2& start_position) : _position(start_position), _next_position(start_position) {}

	virtual ~Particle() = default;

	using Factory = shared_ptr<Particle>(*)(const Vector2&);

	struct RegistryEntry
	{
		string type_name;
		Factory create;
	};

	static vector<RegistryEntry>& get_registry()
	{
		static vector<RegistryEntry> registry;
		return registry;
	}

	const Vector2& get_position() const
	{
		return _position;
	}

	virtual float get_size() const = 0;

	virtual const Color get_color() const = 0;

	virtual float get_max_health() const = 0;

	virtual float get_health_decay() const = 0;

	bool is_type(ParticleType type) const;

	bool can_eat()
	{
		return get_health() <= get_max_health() * _eat_health_threshold;
	}

	const unordered_map<ParticleType, float>& get_attractions()
	{
		if (_attractions.empty()) generate_type_attractions();
		return _attractions;
	}

	void step(const vector<shared_ptr<Particle>>& particles)
	{
		update_acceleration(particles);
		update_velocity();
		update_next_position();
		step_general();
		step_specific(particles);
	}

	void check_collisions(const vector<shared_ptr<Particle>>& particles);

	void update_position()
	{
		_position = _next_position;
	}

protected:
	static inline constexpr float _effect_radius = 2000.0f;
	static inline constexpr float _max_acceleration = numeric_limits<float>::max();
	static inline constexpr float _collision_correction = 0.7f;
	static inline constexpr float _acceleration_scale = 25.0f;
	static inline constexpr float _velocity_scale = 4.0f;
	static inline constexpr float _velocity_decay = 0.8f;
	static inline constexpr float _eat_health_threshold = 0.8f;
	static inline constexpr float _hunger_scaling = 2.0f;
	static inline constexpr float _mutation_range = 5.0f;

	Vector2 _position = { 0.0f, 0.0f };
	Vector2 _next_position = { 0.0f, 0.0f };
	Vector2 _velocity = { 0.0f, 0.0f };
	Vector2 _acceleration = { 0.0f, 0.0f };
	optional<float> _health;

	virtual vector<ParticleType> get_types() const = 0;

	virtual void collide(const vector<shared_ptr<Particle>>& collisions) {}

	static void reproduce(const Vector2& start_position, Particle* parent,
		const function<shared_ptr<Particle>(const Vector2&)> factory);

	virtual void step_specific(const vector<shared_ptr<Particle>>& particles) {}

	virtual float scale_attraction(float attraction, const shared_ptr<const Particle>& other, const RelativePosition& rel_pos)
	{
		return attraction;
	}

	virtual bool ignore_attraction(const shared_ptr<const Particle>& other, const RelativePosition& rel_pos) const;

	float& get_health()
	{
		if (!_health.has_value()) _health.emplace(get_max_health());
		return _health.value();
	}

	float get_health_percent()
	{
		return get_health() / get_max_health();
	}

private:
	unordered_map<ParticleType, float> _attractions;

	void generate_type_attractions();

	void generate_child_attractions(const unordered_map<ParticleType, float>& parent_attractions);

	void update_acceleration(const vector<shared_ptr<Particle>>& particles);

	void update_velocity();

	void update_next_position();

	float scale_attraction_by_dist(float attraction, float distance);

	void step_general();
};

template <typename T>
class RegisterParticle
{
public:
	RegisterParticle(string name)
	{
		Particle::get_registry().push_back(
		{
			name,
			[](const Vector2& start_position) -> shared_ptr<Particle>
			{
				return make_shared<T>(start_position);
			}
		});
	}
};