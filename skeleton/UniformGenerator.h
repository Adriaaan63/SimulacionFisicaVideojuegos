#pragma once
#include "ParticleGenerator.h"
class UniformGenerator : public ParticleGenerator
{
private:
	float radius;
	float timeLifeParticle;
	Particle* particleModel;
public:
	UniformGenerator(physx::PxVec3 pos, float radius, float timeLifeParticle);
	~UniformGenerator() {};
	Particle* generateParticle() override;
	float generateUniform(float min, float max);
};

