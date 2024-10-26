#pragma once
#include "PxPhysics.h"
#include "Particle.h"
class ParticleSystem;
#include <random>
const float GRAVITY = -9.8f;
class ParticleGenerator
{
public:
	ParticleGenerator(physx::PxVec3 pos);
	virtual ~ParticleGenerator();

	void update(double t, ParticleSystem* prSys);
	virtual Particle* generateParticle() = 0;
	physx::PxVec3 getPose() const {
		return pos;
	}
	void setModel(Particle newParticleModel) {
		particleModel = newParticleModel;
	}
protected:
	physx::PxVec3 pos;
	Particle particleModel;
};

