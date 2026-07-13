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

	float get_max_health() const override
	{
		return 150.0f;
	}

	float get_health_decay() const override
	{
		return 2.0f;
	}

	unsigned short get_id() const override
	{
		return id;
	}

protected:
	vector<ParticleType> get_types() const override
	{
		return { ParticleType::Scavenger };
	}

	void collide(const vector<shared_ptr<Particle>>& collisions) override;

	float scale_attraction(float attraction, const shared_ptr<const Particle>& other, const RelativePosition& rel_pos) override;

	void write_unique_data(ofstream& stream) const override;

	void read_unique_data(ifstream& stream) override;

private:
	static inline constexpr int _waste_to_reproduce = 3;
	int _current_waste = 0;

	static inline constexpr unsigned short id = 2;
	static inline RegisterParticle<Scavenger> reg{ id, "Scavenger" };
};