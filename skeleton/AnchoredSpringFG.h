#pragma once
#include "SpringForceGenerator.h"
class AnchoredSpringFG: public SpringForceGenerator
{
public:
	AnchoredSpringFG(double k, double resting, const physx::PxVec3& anchor_pos);
	~AnchoredSpringFG();

};

