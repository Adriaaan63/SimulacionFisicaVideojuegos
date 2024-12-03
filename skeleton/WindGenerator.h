#pragma once
#include "ForceGenerator.h"
class WindGenerator : public ForceGenerator
{
public:
	WindGenerator(const physx::PxVec3& velocidad, float k1, float k2, physx::PxVec3 centro, float radio);
	virtual physx::PxVec3 calculateForce(Particle* p);
	virtual physx::PxVec3  calculateForceSolid(SolidoRigido* p);
	virtual ~WindGenerator() {};
	virtual void calculateVel(Particle* p) {};
	virtual void calculateVelSolid(SolidoRigido* p) {};
protected:
	physx::PxVec3 velocidad;
	float k1 , k2;
	physx::PxVec3 centro;
	float radio;
};


