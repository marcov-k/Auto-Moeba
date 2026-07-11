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
		return { ParticleType::Waste };
	}

	void collide(const vector<shared_ptr<Particle>>& collisions) override;

	void step_specific(const vector<shared_ptr<Particle>>& particles) override;

	float scale_attraction(float attraction, const shared_ptr<const Particle>& other, const RelativePosition& rel_pos) const override;

private:
	static inline RegisterParticle<Waste> reg{ "Waste" };
};