#pragma once

#include "Particle.h"

class Membrane : public Particle
{
public:
	using Particle::Particle;

	float get_size() const override
	{
		return 18.0f;
	}

	const Color get_color() const override
	{
		return SKYBLUE;
	}

	float get_max_health() const override
	{
		return 150.0f;
	}

	float get_health_decay() const override
	{
		return 2.0f;
	}

protected:
	vector<ParticleType> get_types() const override
	{
		return { ParticleType::Membrane, ParticleType::Prey };
	}

	void collide(const vector<shared_ptr<Particle>>& collisions) override;

private:
	static inline constexpr int _food_to_reproduce = 1;
	int _current_food = 0;

	static inline RegisterParticle<Membrane> reg{ "Membrane" };
};