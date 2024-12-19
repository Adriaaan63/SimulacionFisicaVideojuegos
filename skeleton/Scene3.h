#pragma once
#include "Scene.h"
#include "SolidosRSystem.h"
#include "ParticleSystem.h"
#include "FireWorkGenerator.h"
using namespace physx;
class Scene3: public Scene
{
public:
	Scene3() {};
	Scene3(PxPhysics* gPhysics, PxScene* gScene);
	~Scene3();
	virtual void onCollision(physx::PxRigidActor* actor1, physx::PxRigidActor* actor2);
	
	virtual void Update(double t);
	virtual void init(ProjectileTrajectoryGenerator*& trajectoryGen, int puntosTotales);
	virtual void createProyectil() {};
private:
	void createScene();
	double timer = 0;
	double timeToFireWork = 2;
};

