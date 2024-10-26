#pragma once
#include "ParticleGenerator.h"
class NormalGenerator : public ParticleGenerator
{
private:
	float radius;
	float timeLifeParticle;
	float posMax;
	float posMin;
public:
	NormalGenerator(physx::PxVec3 pos, float radius, float timeLifeParticle, float posMax, float posMin);
	~NormalGenerator() {};
	Particle* generateParticle() override;
	float generateGausssian(float mean, float stddev);
	
};

