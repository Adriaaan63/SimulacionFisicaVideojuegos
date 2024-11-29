#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "PxPhysics.h"
class SolidoRigido
{
private:
	physx::PxRigidDynamic* newSolid;
public:
	SolidoRigido(physx::PxPhysics* gPhysics,physx::PxTransform transform, physx::PxVec3 linVel, physx::PxVec3 angVel, physx::PxVec3 tam);
	~SolidoRigido();

	physx::PxRigidDynamic* getSolido() const {
		return newSolid;
	}
};

