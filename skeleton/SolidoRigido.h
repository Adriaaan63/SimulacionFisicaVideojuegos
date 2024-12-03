#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "PxPhysics.h"
class SolidoRigido
{
private:
	physx::PxRigidDynamic* newSolid;
	physx::PxShape* shape;
	physx::PxScene* gScene;
	physx::PxTransform pose;
	physx::PxVec3 tam;
	float timeLife;
	RenderItem* dynamicItem;
public:
	SolidoRigido() {};
	SolidoRigido(physx::PxScene* gScene,physx::PxTransform transform, physx::PxVec3 linVel, physx::PxVec3 angVel, physx::PxVec3 tam);
	SolidoRigido(SolidoRigido& const s);
	SolidoRigido& operator=(const SolidoRigido& p) {
		newSolid = p.newSolid;
		shape = p.shape;
		gScene = p.gScene;
		tam = p.tam;
		return *this;
	}
	~SolidoRigido() {
		newSolid->release();
		if (dynamicItem != nullptr)
			DeregisterRenderItem(dynamicItem);
	};

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
	}
	physx::PxVec3 getTam() const { return tam; };
	bool isAlive();
	void integrate(double t);
};

