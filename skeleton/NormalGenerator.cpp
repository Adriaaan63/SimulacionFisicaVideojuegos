#include "NormalGenerator.h"
NormalGenerator::NormalGenerator(physx::PxVec3 pos, float radius, float timeLifeParticle, float posMax, float posMin) :
	ParticleGenerator(pos), 
	radius(radius), timeLifeParticle(timeLifeParticle),
	posMax(posMax), posMin(posMin){
	//particleModel = new Particle(pos, physx::PxVec3(0, 0, 0), physx::PxVec3(0, -9.8, 0));
};

Particle* NormalGenerator::generateParticle() {
	/*Particle* p = new Particle(pos, physx::PxVec3(generateGausssian(0.0, 2), generateGausssian(20, 2), generateGausssian(0, 2)), Vector3(0, -9.8, 0), 0.99);
	p->setRadius(radius);
	p->setTimeLife(timeLifeParticle);
	return p;*/
	Particle* p = new Particle(particleModel);

	p->setVel(physx::PxVec3(generateGausssian(0.0, 2), generateGausssian(20, 2), generateGausssian(0, 2)));
	/*p->setPose(physx::PxTransform(pos));*/
	p->setRadius(radius);
	p->setTimeLife(timeLifeParticle);
	return p;
}
float NormalGenerator::generateGausssian(float mean, float stddev)
{
	static std::default_random_engine generator;
	std::normal_distribution<float>distribution(mean, stddev);
	return distribution(generator);
}