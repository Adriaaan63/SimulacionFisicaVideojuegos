#pragma once
#include "PxPhysics.h"
#include "Particle.h"
class ParticleSystem;
#include <random>
const float GRAVITY = 10.0f;
class ParticleGenerator
{
public:
	ParticleGenerator(physx::PxVec3 pos);
	virtual ~ParticleGenerator();

	void update(double t, ParticleSystem* prSys);
	virtual Particle* generateParticle() = 0;
protected:
	physx::PxVec3 pos;
	
};

