#include "TornadoGenerator.h"
TornadoGenerator::TornadoGenerator(const physx::PxVec3& velocidad, float k1, float k2, physx::PxVec3 centro, float radio, float intensity) :
	WindGenerator(velocidad, k1, k2, centro, radio), intensity(intensity) {
}

void TornadoGenerator::calculateVel(Particle* p) {
	physx::PxVec3 vTor = {-(p->getPose().p.z - centro.z), 0, p->getPose().p.x - centro.x };
	velocidad = intensity * vTor;
}
void TornadoGenerator::calculateVelSolid(SolidoRigido* p) {
	physx::PxVec3 vTor = { -(p->getPose().p.z - centro.z), 0, p->getPose().p.x - centro.x };
	velocidad = intensity * vTor;
}