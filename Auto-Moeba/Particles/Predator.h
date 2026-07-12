#pragma once

#include "Particle.h"

class Predator : public Particle
{
public:
	using Particle::Particle;

	float get_size() const override
	{
		return 20.0f;
	}

	const Color get_color() const override
	{
		return RED;
	}

	float get_max_health() const override
	{
		return 100.0f;
	}

	float get_health_decay() const override
	{
		return 2.0f;
	}

protected:
	vector<ParticleType> get_types() const override
	{
		return { ParticleType::Predator };
	}

	void collide(const vector<shared_ptr<Particle>>& collisions) override;

	float scale_attraction(float attraction, const shared_ptr<const Particle>& other, const RelativePosition& rel_pos) override;

private:
	static inline constexpr int _prey_to_reproduce = 4;
	int _current_prey = 0;

	static inline RegisterParticle<Predator> reg{ "Predator" };
};