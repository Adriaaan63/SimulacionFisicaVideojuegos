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
		Particle p = Particle(g->getPose(), physx::PxVec3(0,0,0), physx::PxVec3(0, GRAVITY, 0));
		g->setModel(p);
		generators.push_back(g);
	}
	std::list<Particle*> getListPart() const { return particles; };
	void addParticle(Particle* p);
};

