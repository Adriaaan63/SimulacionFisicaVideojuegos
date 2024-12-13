#pragma once
#include "SolidosRSystem.h"
#include "ParticleSystem.h"
#include "ExplosionForceGenerator.h"
#include "ProjectileTrajectoryGenerator.h"
#include "NormalGenerator.h"
#include "GravityForceGenerator.h"
#include "Scene.h"

class ProjectileTrajectoryGenerator;
using namespace physx;
class Scene1: public Scene
{
public:
	Scene1() {};
	Scene1(PxPhysics* gPhysics, PxScene* gScene);
	~Scene1();
	virtual void onCollision(physx::PxRigidActor* actor1, physx::PxRigidActor* actor2);
	virtual void Update(double t);
	
	bool getCanDrawTray() const { return canDrawTray; }
	ProjectileTrajectoryGenerator* getTrayectGen() const { return trajectoryGen; }

	void createProyectil();
	SolidosRSystem* getSolidSys() const { return solidSys; };
private:
	SolidosRSystem* solidSys;
	ParticleSystem* parSys;
	ProjectileTrajectoryGenerator* trajectoryGen;

	void createScene();
	void creteSuelo(physx::PxScene* gScene, physx::PxGeometry* geo, physx::PxTransform transform, physx::PxMaterial* material, Vector4 color);
	void createTrayectoria();
	
	bool canDrawTray;
	SolidosEstaticos* suelo;
	
	
};

