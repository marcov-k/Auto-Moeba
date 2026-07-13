#pragma once

#include "Particle.h"

class Membrane : public Particle
{
public:
	using Particle::Particle;

	float get_size() const override
	{
		return 18.0f;
	}

	const Color get_color() const override
	{
		return SKYBLUE;
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
		return { ParticleType::Membrane };
	}

	void collide(const vector<shared_ptr<Particle>>& collisions) override;

	float scale_attraction(float attraction, const shared_ptr<const Particle>& other, const RelativePosition& rel_pos) override;

	bool ignore_attraction(const shared_ptr<const Particle>& other, const RelativePosition& rel_pos) const override;

	void write_unique_data(ofstream& stream) const override;

	void read_unique_data(ifstream& stream) override;

private:
	static inline constexpr float _min_dist_mult = 1.75f;
	static inline constexpr int _food_to_reproduce = 1;
	int _current_food = 0;

	static inline constexpr unsigned short id = 3;
	static inline RegisterParticle<Membrane> reg{ id, "Membrane" };
};