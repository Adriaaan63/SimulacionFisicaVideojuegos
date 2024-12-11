#pragma once
#include "SolidosRSystem.h"
#include "ParticleSystem.h"
#include "ExplosionForceGenerator.h"
#include "ProjectileTrajectoryGenerator.h"
#include "NormalGenerator.h"

class ProjectileTrajectoryGenerator;
using namespace physx;
class Scene1
{
public:
	Scene1() {};
	Scene1(PxPhysics* gPhysics, PxScene* gScene);
	~Scene1();
	void onCollision(physx::PxRigidActor* actor1, physx::PxRigidActor* actor2);
	void Update(double t);
	
	bool getCanDrawTray() const { return canDrawTray; }
	ProjectileTrajectoryGenerator* getTrayectGen() const { return trajectoryGen; }

	void createProyectil();
private:
	PxPhysics* gPhysics;
	PxScene* gScene;

	SolidosRSystem* solidSys;
	ParticleSystem* parSys;
	ProjectileTrajectoryGenerator* trajectoryGen;

	void createScene();
	void createTrayectoria();
	
	bool canDrawTray;
	
};
