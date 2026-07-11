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
	size_t removed_count = 0;
	for (size_t i = 0; i < particles.size(); ++i)
	{
		for (auto& particle : removed)
		{
			if (particles[i].get() == particle)
			{
				particle->kill();
				particles.erase(particles.begin() + i - removed_count);
				removed_count++;
				break;
			}
		}
	}
	removed.clear();
}