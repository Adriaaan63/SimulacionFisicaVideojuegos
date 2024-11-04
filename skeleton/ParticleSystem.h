#pragma once
#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "ForceGenerator.h"
class ParticleSystem
{
protected:
	std::list<Particle*> particles;
	std::list<ParticleGenerator*> generators;
	std::list<ForceGenerator*> forceGenerators;
public:
	ParticleSystem();
	~ParticleSystem();

	virtual void update(double t);
	void createGenerator(ParticleGenerator* g, float massP) {
		Particle p = Particle(g->getPose(), physx::PxVec3(0,0,0), massP);
		g->setModel(p);
		generators.push_back(g);
	}
	void createForceGenerator(ForceGenerator* g) {
		forceGenerators.push_back(g);
	}
	std::list<Particle*> getListPart() const { return particles; };
	void addParticle(Particle* p);

	void applyForces(Particle* p);
};

