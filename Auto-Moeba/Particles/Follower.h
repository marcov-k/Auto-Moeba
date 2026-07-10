#pragma once

#include "Particle.h"

class Follower : public Particle
{
public:
	using Particle::Particle;

	float get_size() const override
	{
		return 13.0f;
	}

	const Color get_color() const override
	{
		return SKYBLUE;
	}

	void collide() override {}

private:
	static inline constexpr float _speed = 300.0f;
	static inline constexpr float _follow_range = 600.0f;
	static inline constexpr float _follow_dist = 400.0f;
	static inline constexpr float _eps = 10.0f;

	shared_ptr<Particle> _target = nullptr;

	static inline RegisterParticle<Follower> reg{ "Follower" };

	void generate_next_position(const vector<shared_ptr<Particle>>& particles) override;
};