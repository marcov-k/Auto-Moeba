#pragma once

#include "Particle.h"

class Chaser : public Particle
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

	void collide() override {}

private:
	static inline constexpr float _speed = 200.0f;

	static inline RegisterParticle<Chaser> reg{ "Chaser" };

	void generate_next_position(const vector<shared_ptr<Particle>>& particles) override;
};