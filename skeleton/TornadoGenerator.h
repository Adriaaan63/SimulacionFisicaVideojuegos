#pragma once
#include "WindGenerator.h"
class TornadoGenerator: public WindGenerator
{
private:
	float intensity;
public:
	TornadoGenerator(const physx::PxVec3& velocidad, float k1, float k2, physx::PxVec3 centro, float radio, float intensity);
	~TornadoGenerator() {};
	void calculateVel(Particle* p) override;
	void calculateVelSolid(SolidoRigido* p) override;
};

