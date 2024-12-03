#pragma once
#include <cmath>
#include "ForceGenerator.h"
class ExplosionForceGenerator: public ForceGenerator
{
public:
	ExplosionForceGenerator(const physx::PxVec3& centro, float radio, float k, float ct);
	physx::PxVec3 calculateForce(Particle* p) override;
	physx::PxVec3  calculateForceSolid(SolidoRigido* p) override;
	virtual ~ExplosionForceGenerator() {};
	void caldulateDistance(Particle* p);
	void caldulateDistanceSolid(SolidoRigido* p);
	virtual void update(double t, ParticleSystem* prSys);
	virtual void updateSolido(double t, SolidosRSystem* sSys);
private:
	physx::PxVec3 centro;
	float radio, k, ct, d;
};

