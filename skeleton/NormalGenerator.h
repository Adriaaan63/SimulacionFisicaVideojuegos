#pragma once
#include "ParticleGenerator.h"
class NormalGenerator : public ParticleGenerator
{
private:
	float radius;
public:
	NormalGenerator(physx::PxVec3 pos,float radius) :ParticleGenerator(pos){};
	~NormalGenerator() {};
	Particle* generateParticle() override{
		Particle* p = new Particle();
		p->setPose(particleModel->getPose());
		p->setVel(physx::PxVec3(generateGausssian(0.0, 2), generateGausssian(20, 2), generateGausssian(0, 2)));
		p->setAcceleration(particleModel->getAcc());
		p->setDamping(particleModel->getDamping());
		p->setRenderItem(particleModel->getRenderItem());
		return p;
	}
	float generateGausssian(float mean, float stddev)
	{
		static std::default_random_engine generator;
		std::normal_distribution<float>distribution(mean, stddev);
		return distribution(generator);
	}
};

