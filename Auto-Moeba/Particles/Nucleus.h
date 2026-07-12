#pragma once

#include "Particle.h"

class Nucleus : public Particle
{
public:
	using Particle::Particle;

	float get_size() const override
	{
		return 23.0f;
	}

	const Color get_color() const override
	{
		return VIOLET;
	}

	float get_max_health() const override
	{
		return 200.0f;
	}

	float get_health_decay() const override
	{
		return 2.0f;
	}

protected:
	vector<ParticleType> get_types() const override
	{
		return { ParticleType::Nucleus, ParticleType::Prey };
	}

	void collide(const vector<shared_ptr<Particle>>& collisions) override;

	float scale_attraction(float attraction, const shared_ptr<const Particle>& other, const RelativePosition& rel_pos) override;

private:
	static inline constexpr float _min_dist_mult = 1.1f;
	static inline constexpr int _food_to_reproduce = 3;
	int _current_food = 0;

	static inline RegisterParticle<Nucleus> reg{ "Nucleus" };
};