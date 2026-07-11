#pragma once

#include "Particle.h"

class Waste : public Particle
{
public:
	using Particle::Particle;

	float get_size() const override
	{
		return 13.0f;
	}

	const Color get_color() const override
	{
		return GRAY;
	}

protected:
	vector<ParticleType> get_types() const override
	{
		return { ParticleType::Waste };
	}

	void collide(const vector<shared_ptr<Particle>>& collisions) override;

	float scale_attraction(float attraction, const shared_ptr<const Particle>& other, const RelativePosition& rel_pos) const override;

private:
	static inline RegisterParticle<Waste> reg{ "Waste" };
};