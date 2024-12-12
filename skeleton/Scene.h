#pragma once
#include "RenderUtils.hpp"
using namespace physx;
class Scene
{
public:
	Scene() {};
	Scene(PxPhysics* gPhysics, PxScene* gScene);
	~Scene();
	virtual void onCollision(physx::PxRigidActor* actor1, physx::PxRigidActor* actor2) = 0;
	virtual void Update(double t) = 0;


protected:
	PxPhysics* gPhysics;
	PxScene* gScene;
};

