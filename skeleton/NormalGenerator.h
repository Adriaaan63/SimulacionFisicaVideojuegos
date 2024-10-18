#pragma once
#include "ParticleGenerator.h"
class NormalGenerator : public ParticleGenerator
{
private:
	float radius;
public:
	NormalGenerator(physx::PxVec3 pos, float radius) :ParticleGenerator(pos) {};
	~NormalGenerator() {};
	Particle* generateParticle() override {
		std::normal_distribution<float> distrubution(-5.0f, 5.0f);
		std::default_random_engine generator;
		physx::PxVec3 newVel(distrubution(generator), distrubution(generator), distrubution(generator));
		particleModel->setVel(physx::PxVec3(newVel));
		particleModel->setRadius(radius);
		return particleModel;
	}
};

