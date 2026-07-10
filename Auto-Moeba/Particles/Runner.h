#pragma once

#include "Particle.h"

class Runner : public Particle
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

	void collide() override {}

private:
	static inline constexpr float _speed = 200.0f;

	static inline RegisterParticle<Runner> reg{ "Runner" };

	void generate_next_position(const vector<shared_ptr<Particle>>& particles) override;
};