#pragma once

#include <memory>
#include <unordered_set>
#include <vector>

using namespace std;

class Particle;

struct ParticleHandler
{
	static vector<shared_ptr<Particle>> particles;
	static vector<shared_ptr<Particle>> added;
	static unordered_set<Particle*> removed;

	ParticleHandler() = delete;

	static void add_particle(shared_ptr<Particle> particle);

	static void remove_particle(Particle* particle);

	static void finalize_adds();

	static void finalize_removes();

	static void clear_all();
};