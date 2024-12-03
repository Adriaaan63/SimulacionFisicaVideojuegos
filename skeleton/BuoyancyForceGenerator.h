#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
#include <iostream>
class BuoyancyForceGenerator : public ForceGenerator
{
public:
	BuoyancyForceGenerator(float h, float V, float d, physx::PxVec3 fgPos);

	physx::PxVec3 calculateForce(Particle* p) override;
	physx::PxVec3 calculateForceSolid(SolidoRigido* p) override;

	virtual ~BuoyancyForceGenerator() {}

	void setVolume(float increment_volume) {
		if (volume + increment_volume > 0.0f) {
			volume += increment_volume;
			std::cout << volume << std::endl;
		}
	}

protected:
	float height;
	float volume;
	float density;
	float _gravitity = 9.8f;

	Particle* liquidParticle;
};

