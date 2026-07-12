#include "ParticleHandler.h"
#include "Particles/Particle.h"

vector<shared_ptr<Particle>> ParticleHandler::particles;
vector<shared_ptr<Particle>> ParticleHandler::added;
unordered_set<Particle*> ParticleHandler::removed;

void ParticleHandler::add_particle(shared_ptr<Particle> particle)
{
	added.push_back(particle);
}

void ParticleHandler::remove_particle(Particle* particle)
{
	removed.insert(particle);
}

void ParticleHandler::finalize_adds()
{
	particles.reserve(particles.size() + added.size());
	for (auto& particle : added)
	{
		particles.push_back(particle);
	}
	added.clear();
}

void ParticleHandler::finalize_removes()
{
	if (removed.size() < 1) return;

	particles.erase(
		remove_if(particles.begin(), particles.end(),
			[](const shared_ptr<Particle>& p)
			{
				return (bool)removed.count(p.get());
			}),
		particles.end()
	);
	removed.clear();
}