#include "ExplosionForceGenerator.h"
#include "ParticleSystem.h"
#include "SolidosRSystem.h"
ExplosionForceGenerator::ExplosionForceGenerator(const physx::PxVec3& centro, float radio, float k, float ct) :
	ForceGenerator(ct * 4),
	centro(centro), radio(radio), k(k), ct(ct), d(0) {
	
}

void ExplosionForceGenerator::update(double t, ParticleSystem* prSys) {
	duration -= t;
	if (duration < 0) {
		alive = false;
		prSys->setExplosion(false);
	}
}

void ExplosionForceGenerator::updateSolido(double t, SolidosRSystem* sSys)
{
	duration -= t;
	if (duration < 0) {
		alive = false;
		sSys->setExplosion(false);
	}
}

physx::PxVec3 ExplosionForceGenerator::calculateForce(Particle* p) {
	
	if (d < radio) {
		caldulateDistance(p);
		physx::PxVec3 forceExplosion = (k/pow(d,2)) * physx::PxVec3(p->getPose().p.x - centro.x, p->getPose().p.y - centro.y, p->getPose().p.z - centro.z) * std::exp(-duration/ct);
		return forceExplosion;
	}
	else 
		return physx::PxVec3(0, 0, 0);
}
physx::PxVec3 ExplosionForceGenerator::calculateForceSolid(SolidoRigido* p)
{
	if (d < radio) {
		caldulateDistanceSolid(p);
		physx::PxVec3 forceExplosion = (k / pow(d, 2)) * physx::PxVec3(p->getSolido()->getGlobalPose().p.x - centro.x, p->getSolido()->getGlobalPose().p.y - centro.y, p->getSolido()->getGlobalPose().p.z - centro.z) * std::exp(-duration / ct);
		return forceExplosion;
	}
	else
		return physx::PxVec3(0, 0, 0);
}
void ExplosionForceGenerator::caldulateDistance(Particle* p) {
	d = sqrt(pow(p->getPose().p.x - centro.x, 2) + 
		pow(p->getPose().p.y - centro.y, 2) +
		pow(p->getPose().p.z - centro.z, 2));
}
void ExplosionForceGenerator::caldulateDistanceSolid(SolidoRigido* p) {
	d = sqrt(pow(p->getSolido()->getGlobalPose().p.x - centro.x, 2) +
		pow(p->getSolido()->getGlobalPose().p.y - centro.y, 2) +
		pow(p->getSolido()->getGlobalPose().p.z - centro.z, 2));
}