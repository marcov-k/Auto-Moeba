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
	static inline constexpr float _speed = 400.0f;
	static inline constexpr float _min_detect_range = 400.0f;
	static inline constexpr float _run_range = 1000.0f;

	bool _running = false;

	static inline RegisterParticle<Runner> reg{ "Runner" };

	void generate_next_position(const vector<shared_ptr<Particle>>& particles) override;
};