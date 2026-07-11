#include "ParticleHandler.h"

vector<shared_ptr<Particle>> ParticleHandler::particles;
vector<shared_ptr<Particle>> ParticleHandler::added;
vector<Particle*> ParticleHandler::removed;

void ParticleHandler::add_particle(shared_ptr<Particle> particle)
{
	added.push_back(particle);
}

void ParticleHandler::remove_particle(Particle* particle)
{
	removed.push_back(particle);
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
	for (auto& particle : removed)
	{
		for (size_t i = 0; i < particles.size(); ++i)
		{
			if (particles[i].get() == particle)
			{
				particles.erase(particles.begin() + i);
				break;
			}
		}
	}
	removed.clear();
}