#pragma once

#include "Particle.h"

class Anchor : public Particle
{
public:
	using Particle::Particle;

	float get_size() const override
	{
		return 30.0f;
	}

	const Color get_color() const override
	{
		return DARKGREEN;
	}

	float get_max_health() const override
	{
		return 500.0f;
	}

	float get_health_decay() const override
	{
		return 2.0f;
	}

protected:
	vector<ParticleType> get_types() const override
	{
		return { ParticleType::Anchor };
	}

private:
	static inline RegisterParticle<Anchor> reg{ "Anchor" };
};