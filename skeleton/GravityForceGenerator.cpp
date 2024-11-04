#include "GravityForceGenerator.h"
GravityForceGenerator::GravityForceGenerator(const Vector3& gravity) :ForceGenerator(), gravity(gravity) {

};
physx::PxVec3 GravityForceGenerator::calculateForce(Particle* p) {
	return gravity * p->getMass();
}