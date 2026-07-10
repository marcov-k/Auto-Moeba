#pragma once

#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <typeinfo>
#include <vector>

#include "raylib.h"
#include "../Utilities.h"

using namespace std;

class Particle
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

	void step(const vector<shared_ptr<Particle>>& particles)
	{
		generate_next_position(particles);
		_collisions = check_collisions(particles);
	}

	const vector<shared_ptr<Particle>> check_collisions(const vector<shared_ptr<Particle>>& particles);

	virtual void collide() = 0;

	void update_position()
	{
		_position = _next_position;
	}

protected:
	Vector2 _position = { 0.0f, 0.0f };
	Vector2 _next_position = { 0.0f, 0.0f };
	vector<shared_ptr<Particle>> _collisions;

private:
	virtual void generate_next_position(const vector<shared_ptr<Particle>>& particles) = 0;
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