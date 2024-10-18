#pragma once
#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"
class ParticleSystem
{
protected:
	std::list<Particle*> particles;
	std::list<ParticleGenerator*> generators;
public:
	ParticleSystem();
	~ParticleSystem();

	virtual void update(double t);
	void createGenerator(ParticleGenerator* g) {
		generators.push_back(g);
	}
};

