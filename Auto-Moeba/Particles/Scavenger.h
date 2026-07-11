#pragma once

#include "Particle.h"

class Scavenger : public Particle
{
public:
	using Particle::Particle;

	float get_size() const override
	{
		return 17.0f;
	}

	const Color get_color() const override
	{
		return LIGHTGRAY;
	}

protected:
	vector<ParticleType> get_types() const override
	{
		return { ParticleType::Scavenger };
	}

	void collide(const vector<shared_ptr<Particle>>& collisions) override;

	float scale_attraction(float attraction, const shared_ptr<const Particle>& other, const RelativePosition& rel_pos) const override;

private:
	static inline constexpr int _waste_to_reproduce = 3;
	static int _current_waste;

	static inline RegisterParticle<Scavenger> reg{ "Scavenger" };
};