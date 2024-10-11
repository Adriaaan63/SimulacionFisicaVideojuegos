#pragma once
#include "PxPhysics.h"
#include "Particle.h"

class ParticleGenerator
{
public:
	ParticleGenerator(physx::PxVec3 pos);
	~ParticleGenerator();

	void generateParticle();
private:
	physx::PxVec3 pos;
	Particle* particleModel; 
};

