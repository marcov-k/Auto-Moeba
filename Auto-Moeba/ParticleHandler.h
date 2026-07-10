#pragma once

#include <memory>
#include <vector>

using namespace std;

class Particle;

struct ParticleHandler
{
	static vector<shared_ptr<Particle>> particles;
	static vector<Particle*> removed;

	ParticleHandler() = delete;

	static void add_particle(shared_ptr<Particle> particle);

	static void remove_particle(Particle* particle);

	static void finalize_removes();
};