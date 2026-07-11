#pragma once

#include "Particle.h"

class Food : public Particle
{
public:
	using Particle::Particle;

	float get_size() const override
	{
		return 12.0f;
	}

	const Color get_color() const override
	{
		return BROWN;
	}

	float get_max_health() const override
	{
		return 1.0f;
	}

	float get_health_decay() const override
	{
		return 0.0f;
	}

protected:
	vector<ParticleType> get_types() const override
	{
		return { ParticleType::Food };
	}

	void collide(const vector<shared_ptr<Particle>>& collisions) override;

private:
	static inline RegisterParticle<Food> reg{ "Food" };
};