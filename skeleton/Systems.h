#pragma once
#include <list>
#include "ParticleGenerator.h"
#include "ForceGenerator.h"
#include <iostream>
class Systems
{
protected:
	std::list<ParticleGenerator*> generators;
	std::list<ForceGenerator*> forceGenerators;
	bool activeExplosion;
public:
	Systems(){}
	virtual ~Systems() {
		for (auto g : generators) {
			delete g;
		}
		generators.clear();
		for (auto fg : forceGenerators) {
			delete fg;
		}
		forceGenerators.clear();
	}
	virtual void update(double t) = 0;
	void createForceGenerator(ForceGenerator* g) {
		forceGenerators.push_back(g);
	}
	void addParticle(Particle* p);
	void setExplosion(bool active) { activeExplosion = active; };
};

