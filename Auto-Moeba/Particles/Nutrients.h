#pragma once

#include "Particle.h"

class Nutrients : public Particle
{
public:
	using Particle::Particle;

	float get_size() const override
	{
		return 10.0f;
	}

	const Color get_color() const override
	{
		return DARKGREEN;
	}

	float get_max_health() const override
	{
		return 1.0f;
	}

	float get_health_decay() const override
	{
		return 0.0f;
	}

	unsigned short get_id() const override
	{
		return id;
	}

protected:
	vector<ParticleType> get_types() const override
	{
		return {};
	}

	void step_specific(const vector<shared_ptr<Particle>>& particles) override;

	void write_unique_data(ofstream& stream) const override;

	void read_unique_data(ifstream& stream) override;

private:
	static inline constexpr float _growth_time = 10.0f;
	float _current_growth = 0.0f;

	static inline constexpr unsigned short id = 8;
	static inline RegisterParticle<Nutrients> reg{ id, "Nutrients" };
};