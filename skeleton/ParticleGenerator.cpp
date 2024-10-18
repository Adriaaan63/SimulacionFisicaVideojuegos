#include "ParticleGenerator.h"
ParticleGenerator::ParticleGenerator(physx::PxVec3 pos) : pos(pos), particleModel(new Particle(pos,Vector3(0,0,0),Vector3(0,GRAVITY,0),0.99)) {

}
ParticleGenerator::~ParticleGenerator(){

}
