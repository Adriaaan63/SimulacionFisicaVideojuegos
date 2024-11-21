#pragma once
#include "ForceGenerator.h"
class GravityForceGenerator: public ForceGenerator
{
public:
	GravityForceGenerator(const physx::PxVec3& gravity);
	GravityForceGenerator(const physx::PxVec3& gravity,float dur );
	physx::PxVec3 calculateForce(Particle* p) override;
	virtual ~GravityForceGenerator() {};
	virtual void update(double t, ParticleSystem* prSys);
private:
	physx::PxVec3 gravity;
};

