#pragma once

#include "Particle.h"

class Sticker : public Particle
{
public:
	using Particle::Particle;

	float get_size() const override
	{
		return 25.0f;
	}

	const Color get_color() const override
	{
		return BROWN;
	}

	void collide() override;

	shared_ptr<Particle> get_stuck_to() const
	{
		return _stuck_to;
	}

private:
	shared_ptr<Particle> _stuck_to = nullptr;
	Vector2 _stuck_offset = { 0.0f, 0.0f };

	static inline RegisterParticle<Sticker> reg{ "Sticker" };

	void generate_next_position(const vector<shared_ptr<Particle>>& particles) override;
};