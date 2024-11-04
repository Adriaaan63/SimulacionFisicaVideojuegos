#pragma once
#include "ForceGenerator.h"
class GravityForceGenerator: public ForceGenerator
{
public:
	GravityForceGenerator(const physx::PxVec3& gravity);
	physx::PxVec3 calculateForce(Particle* p) override;
	virtual ~GravityForceGenerator() {};
private:
	physx::PxVec3 gravity;
};

