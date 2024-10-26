#include "UniformGenerator.h"
UniformGenerator::UniformGenerator(physx::PxVec3 pos, float radius, float timeLifeParticle) :ParticleGenerator(pos), radius(radius), timeLifeParticle(timeLifeParticle) {
	particleModel = new Particle(pos, physx::PxVec3(0, 0, 0), physx::PxVec3(0, -9.8, 0));
};
Particle* UniformGenerator::generateParticle() {
	Particle* p = new Particle(pos, physx::PxVec3(generateUniform(-20, 20), generateUniform(30, 40), generateUniform(-20, 20)), Vector3(0, -9.8, 0), 0.99);
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