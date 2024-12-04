#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "PxPhysics.h"
#include "geometry/PxGeometry.h"
class SolidoRigido
{
private:
	physx::PxRigidDynamic* newSolid;
	physx::PxShape* shape;
	physx::PxScene* gScene;
	physx::PxTransform pose;
	float timeLife;
	RenderItem* dynamicItem;
public:
	SolidoRigido() {};
	SolidoRigido(physx::PxScene* gScene,physx::PxGeometry* geo,physx::PxTransform transform,
		physx::PxVec3 linVel, physx::PxVec3 angVel, float mass, physx::PxMaterial* material);
	SolidoRigido(SolidoRigido& const s);
	SolidoRigido& operator=(const SolidoRigido& p) {
		newSolid = p.newSolid;
		shape = p.shape;
		gScene = p.gScene;
		return *this;
	}
	~SolidoRigido() {
		newSolid->release();
		if (dynamicItem != nullptr)
			DeregisterRenderItem(dynamicItem);
	};
	physx::PxVec3 calculateInertiaTensor(float mass);
	physx::PxRigidDynamic* getSolido() const {
		return newSolid;
	}
	physx::PxTransform getPose() const { return pose; };
	void setPose(physx::PxTransform newPose) { pose = newPose; };
	void setUpdateSolid(double inercia);
	physx::PxShape* getShape() const {
		return shape;
	}
	physx::PxMaterial* getMaterial() const {
		if (shape) { 
			physx::PxMaterial* material = nullptr;
			shape->getMaterials(&material, 1);
			return material;
		}
		return nullptr; 
	}
	physx::PxPhysics* getGPhysics() const {
		return &gScene->getPhysics();
	}
	void setSolidoInScene() {
		gScene->addActor(*newSolid);
	};
	bool isAlive();
	void integrate(double t);
};

