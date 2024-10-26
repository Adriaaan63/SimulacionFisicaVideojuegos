#include "NormalGenerator.h"
NormalGenerator::NormalGenerator(physx::PxVec3 pos, float radius, float timeLifeParticle, float posMax, float posMin, physx::PxVec3 means, physx::PxVec3 stdDevs) :
	ParticleGenerator(pos, posMax, posMin), 
	radius(radius), timeLifeParticle(timeLifeParticle),
	means(means), stdDevs(stdDevs){
	//particleModel = new Particle(pos, physx::PxVec3(0, 0, 0), physx::PxVec3(0, -9.8, 0));
};

Particle* NormalGenerator::generateParticle() {
	Particle* p = new Particle(particleModel);

	p->setVel(physx::PxVec3(generateGausssian(means.x, stdDevs.x), generateGausssian(means.y, stdDevs.y), generateGausssian(means.z, stdDevs.z)));
	p->setPose(physx::PxTransform(calculatePosicion()));
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