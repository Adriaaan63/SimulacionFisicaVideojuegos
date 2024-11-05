#pragma once
#include "ForceGenerator.h"
class WindGenerator : public ForceGenerator
{
public:
	WindGenerator(const physx::PxVec3& velocidad, float k1, float k2, physx::PxVec3 centro, float radio);
	physx::PxVec3 calculateForce(Particle* p) override;
	virtual ~WindGenerator() {};
private:
	physx::PxVec3 velocidad;
	float k1 , k2;
	physx::PxVec3 centro;
	float radio;
};


