#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "PxPhysics.h"
#include "geometry/PxGeometry.h"
class Solidos
{
protected:
	physx::PxTransform pose;
	physx::PxShape* shape;
	RenderItem* renderItem;
	physx::PxScene* gScene;
public:
	Solidos() {};
	Solidos(physx::PxScene* gScene, physx::PxGeometry* geo, physx::PxTransform transform, physx::PxMaterial* material);
	~Solidos() {
		if (renderItem != nullptr)
			DeregisterRenderItem(renderItem);
	}

	physx::PxTransform getPose() const { return pose; };
	void setPose(physx::PxTransform newPose) { pose = newPose; };
	physx::PxShape* getShape() const {
		return shape;
	}
	physx::PxPhysics* getGPhysics() const {
		return &gScene->getPhysics();
	}
	void setSolidoInScene(physx::PxRigidBody* newSolid) {
		gScene->addActor(*newSolid);
	};
	RenderItem* getRenderItem() const { return renderItem; };
};

