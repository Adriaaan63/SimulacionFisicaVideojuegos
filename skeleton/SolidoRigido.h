#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "PxPhysics.h"
#include "geometry/PxGeometry.h"
#include "Solidos.h"
class SolidoRigido: public Solidos
{
private:
	physx::PxRigidDynamic* newSolid;
	float timeLife;
public:
	SolidoRigido() {};
	SolidoRigido(physx::PxScene* gScene,physx::PxGeometry* geo,physx::PxTransform transform,
		physx::PxVec3 linVel, physx::PxVec3 angVel, float mass, physx::PxMaterial* material, float time = 20);
	SolidoRigido(SolidoRigido& const s);
	SolidoRigido& operator=(const SolidoRigido& p) {
		newSolid = p.newSolid;
		shape = p.shape;
		gScene = p.gScene;
		return *this;
	}
	~SolidoRigido() {
		newSolid->release();
	};
	physx::PxVec3 calculateInertiaTensor(float mass);
	physx::PxRigidDynamic* getSolido() const {
		return newSolid;
	}
	void setUpdateSolid(double inercia);
	physx::PxMaterial* getMaterial() const {
		if (shape) { 
			physx::PxMaterial* material = nullptr;
			shape->getMaterials(&material, 1);
			return material;
		}
		return nullptr; 
	}
	bool isAlive();
	void integrate(double t);
};

