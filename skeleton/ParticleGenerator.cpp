#include "ParticleGenerator.h"
#include "ParticleSystem.h"
ParticleGenerator::ParticleGenerator(physx::PxVec3 pos) : pos(pos) {
}
ParticleGenerator::~ParticleGenerator(){

}
void ParticleGenerator::update(double t, ParticleSystem* prSys) {
	prSys->addParticle(generateParticle());

}
