#include "GravityForceGenerator.h"
GravityForceGenerator::GravityForceGenerator(const Vector3& gravity) :ForceGenerator(INT_MAX), gravity(gravity) {

};
GravityForceGenerator::GravityForceGenerator(const Vector3& gravity, float dur) :ForceGenerator(dur), gravity(gravity) {

};
physx::PxVec3 GravityForceGenerator::calculateForce(Particle* p) {
	return gravity * p->getMass();
}
physx::PxVec3 GravityForceGenerator::calculateForceSolid(SolidoRigido* p)
{
	return gravity * p->getSolido()->getMass();
}
void GravityForceGenerator::update(double t, ParticleSystem* prSys) {
	duration -= t;
	if (duration < 0) {
		alive = false;
	}
}