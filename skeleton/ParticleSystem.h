#pragma once
#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "ForceGenerator.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringFG.h"
#include "BuoyancyForceGenerator.h"
#include <iostream>
#include "Systems.h"
class ParticleSystem: public Systems
{
protected:
	std::list<Particle*> particles;
	/*std::list<ParticleGenerator*> generators;
	std::list<ForceGenerator*> forceGenerators;*/
public:
	ParticleSystem();
	~ParticleSystem();

	virtual void update(double t);
	void createGenerator(ParticleGenerator* g, float massP, Vector4 colorParticle) {
		Particle p = Particle(g->getPose(), physx::PxVec3(0,0,0),colorParticle, massP);
		g->setModel(p);
		generators.push_back(g);
	}

	/*void createForceGenerator(ForceGenerator* g) {
		forceGenerators.push_back(g);
	}*/
	void generateSpringDemo();
	void generateAnchorSpringDemo();
	void generateBuoyancyFG();

	std::list<Particle*> getListPart() const { return particles; };
	void addParticle(Particle* p);

	void applyForces(Particle* p);


	//void setExplosion(bool active) { activeExplosion = active; };

	void setKSpringFG(double newK) {
		f3->setK(f3->getK() + newK);
		std::cout << f3->getK() << std::endl;
	}
	BuoyancyForceGenerator* getFgFlot() const { return f4; };
private:
	//bool activeExplosion;
	AnchoredSpringFG* f3;
	BuoyancyForceGenerator* f4;
};

