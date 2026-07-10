#pragma once

#include "Particle.h"

class Prey : public Particle
{
public:
	using Particle::Particle;

	float get_size() const override
	{
		return 15.0f;
	}

	const Color get_color() const override
	{
		return GREEN;
	}

protected:
	vector<ParticleType> get_types() const override
	{
		return { ParticleType::Prey };
	}

	void collide(const vector<shared_ptr<Particle>>& collisions) override;

	float scale_attraction(float attraction, const shared_ptr<const Particle>& other, const RelativePosition& rel_pos) const override;

private:
	static inline constexpr float _group_dist = 60.0f;

	static inline RegisterParticle<Prey> reg{ "Prey" };
};