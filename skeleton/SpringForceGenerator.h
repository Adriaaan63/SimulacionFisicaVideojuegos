#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
class SpringForceGenerator : public ForceGenerator
{
public:
	SpringForceGenerator(double k, double resting_lenght, Particle* other);

	physx::PxVec3 calculateForce(Particle* p) override;
	physx::PxVec3  calculateForceSolid(SolidoRigido* p) override;

	inline void setK(double k) { _k = k; };
	inline double getK() const { return _k; };

	virtual ~SpringForceGenerator(){}

protected:
	double _k;
	double _resting_lenght;
	Particle* _other;
};

