#pragma once
#include "ParticleGenerator.h"
class UniformGenerator : public ParticleGenerator
{
private:
	float radius;
	float timeLifeParticle;
	physx::PxVec3 mins;
	physx::PxVec3 maxs;
public:
	UniformGenerator(physx::PxVec3 pos, float radius, float timeLifeParticle, float posMax, float posMin, physx::PxVec3 mins, physx::PxVec3 maxs);
	~UniformGenerator() {};
	Particle* generateParticle() override;
	float generateUniform(float min, float max);
	SolidoRigido* generateSolidoRigido() override {
		return nullptr;
	}
};

