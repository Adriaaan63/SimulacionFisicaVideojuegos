#pragma once
#include "ParticleGenerator.h"
class NormalGenerator : public ParticleGenerator
{
private:
	float radius;
	float timeLifeParticle;
	physx::PxVec3 means;
	physx::PxVec3 stdDevs;
public:
	NormalGenerator(physx::PxVec3 pos, float radius, float timeLifeParticle, float posMax, float posMin, physx::PxVec3 means,physx::PxVec3 stdDevs);
	~NormalGenerator() {};
	Particle* generateParticle() override;
	float generateGausssian(float mean, float stddev);
	
};

