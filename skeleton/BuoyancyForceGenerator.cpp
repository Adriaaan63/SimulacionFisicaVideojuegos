#include "BuoyancyForceGenerator.h"
BuoyancyForceGenerator::BuoyancyForceGenerator(float h, float V, float d, physx::PxVec3 fgPos) :
	height(h), volume(V), density(d) {
	liquidParticle = fgPos;
}
physx::PxVec3 BuoyancyForceGenerator::calculateForce(Particle* p) {
	float h = p->getPose().p.y;
	float h0 = liquidParticle.y;

	physx::PxVec3 f(0, 0, 0);
	float inmersed = 0.0;
	if (h - h0 > height * 0.5f) {
		inmersed = 0.0f;
	}
	else if (h0 - h > height * 0.5f) {
		inmersed = 1.0f;
	}
	else {
		inmersed = (h0 - h) / height + 0.5f;
	}
	f.y = density * volume * inmersed;
	return f;
}

physx::PxVec3 BuoyancyForceGenerator::calculateForceSolid(SolidoRigido* p)
{
	float h = p->getSolido()->getGlobalPose().p.y;
	float h0 = liquidParticle.y;

	physx::PxVec3 f(0, 0, 0);
	float inmersed = 0.0;
	if (h - h0 > height * 0.5f) {
		inmersed = 0.0f;
	}
	else if (h0 - h > height * 0.5f) {
		inmersed = 1.0f;
	}
	else {
		inmersed = (h0 - h) / height + 0.5f;
	}
	f.y = density * volume * inmersed;
	return f;
}
