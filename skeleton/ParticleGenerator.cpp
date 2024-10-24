#include "ParticleGenerator.h"
#include "ParticleSystem.h"
ParticleGenerator::ParticleGenerator(physx::PxVec3 pos) : pos(pos) {
	particleModel = new Particle(pos, physx::PxVec3(0, 0, 0), physx::PxVec3(0, -9.8, 0));
}
ParticleGenerator::~ParticleGenerator(){

}
void ParticleGenerator::update(double t, ParticleSystem* prSys) {
	prSys->addParticle(generateParticle());

}
