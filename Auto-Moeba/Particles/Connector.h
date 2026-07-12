#pragma once

#include "Particle.h"

class Connector : public Particle
{
public:
	using Particle::Particle;

	float get_size() const override
	{
		return 14.0f;
	}

	const Color get_color() const override
	{
		return ORANGE;
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
		return { ParticleType::Connector };
	}

	void collide(const vector<shared_ptr<Particle>>& collisions) override;

	float scale_attraction(float attraction, const shared_ptr<const Particle>& other, const RelativePosition& rel_pos) override;

private:
	static inline constexpr float _min_dist_mult = 1.2f;
	static inline constexpr int _food_to_reproduce = 1;
	int _current_food = 0;

	static inline RegisterParticle<Connector> reg{ "Connector" };
};