#pragma once
#include "ParticleGenerator.h"
class UniformGenerator : public ParticleGenerator
{
private:
	float radius;
	float timeLifeParticle;

public:
	UniformGenerator(physx::PxVec3 pos, float radius, float timeLifeParticle) :ParticleGenerator(pos), radius(radius), timeLifeParticle(timeLifeParticle) {};
	~UniformGenerator() {};
	Particle* generateParticle() override {
		/*Particle* p = new Particle();
		p->setPose(particleModel->getPose());
		p->setVel(physx::PxVec3(generateGausssian(0.0, 2), generateGausssian(20, 2), generateGausssian(0, 2)));
		p->setAcceleration(particleModel->getAcc());
		p->setDamping(particleModel->getDamping());
		p->setRenderItem(particleModel->getRenderItem());
		return p;*/

		Particle* p = new Particle(pos, physx::PxVec3(generateUniform(0.0, 2), generateUniform(20, 2), generateUniform(0, 2)), Vector3(0, -9.8, 0), 0.99);
		p->setRadius(radius);
		p->setTimeLife(timeLifeParticle);
		return p;
		/*Particle* p = new Particle(*particleModel);

		p->setVel(physx::PxVec3(generateGausssian(0.0, 2), generateGausssian(20, 2), generateGausssian(0, 2)));
		p->setPose(physx::PxTransform(pos));*/
		return p;
	}
	float generateUniform(float mean, float stddev)
	{
		static std::default_random_engine generator;
		std::normal_distribution<float>distribution(mean, stddev);
		return distribution(generator);
	}
};



