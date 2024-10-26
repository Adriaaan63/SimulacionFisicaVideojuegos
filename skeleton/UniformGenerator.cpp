#include "UniformGenerator.h"
UniformGenerator::UniformGenerator(physx::PxVec3 pos, float radius, float timeLifeParticle, float posMax, float posMin, physx::PxVec3 mins, physx::PxVec3 maxs) :
	ParticleGenerator(pos, posMax, posMin),
	radius(radius), timeLifeParticle(timeLifeParticle),
	mins(mins), maxs(maxs) {
	//particleModel = new Particle(pos, physx::PxVec3(0, 0, 0), physx::PxVec3(0, -9.8, 0));
};
Particle* UniformGenerator::generateParticle() {
	Particle* p = new Particle(particleModel);

	p->setVel(physx::PxVec3(generateUniform(mins.x, maxs.x), generateUniform(mins.y, maxs.y), generateUniform(mins.z, maxs.z)));
	p->setPose(physx::PxTransform(calculatePosicion()));
	p->setRadius(radius);
	p->setTimeLife(timeLifeParticle);
	return p;
}
float UniformGenerator::generateUniform(float min, float max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<> distrib(min, max);
	return distrib(gen);
}