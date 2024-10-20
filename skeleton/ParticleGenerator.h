#pragma once
#include "PxPhysics.h"
#include "Particle.h"
#include <random>
const float GRAVITY = 10.0f;
class ParticleGenerator
{
public:
	ParticleGenerator(physx::PxVec3 pos);
	virtual ~ParticleGenerator();

	virtual Particle* generateParticle() = 0;
protected:
	std::mt19937 random_engine;
	physx::PxVec3 pos;
	Particle* particleModel; 
};

