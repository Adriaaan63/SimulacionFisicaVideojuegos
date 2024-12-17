#pragma once
#include "SolidosRSystem.h"
#include "ParticleSystem.h"
#include "ExplosionForceGenerator.h"
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
	virtual void init(ProjectileTrajectoryGenerator*& trajectoryGen, int puntosTotales);

	bool getCanDrawTray() const { return canDrawTray; }
	ProjectileTrajectoryGenerator* getTrayectGen() const { return trajectoryGen; }

	virtual void createProyectil();
	bool getCambioScene2() const { return cambioScene2; }
private:
	ProjectileTrajectoryGenerator* trajectoryGen;

	void createScene();
	void creteSuelo(physx::PxGeometry* geo, physx::PxTransform transform, physx::PxMaterial* material, Vector4 color);
	void createTrayectoria();
	
	bool canDrawTray;
	SolidosEstaticos* suelo;
	bool cambioScene2 = false;
	
};

