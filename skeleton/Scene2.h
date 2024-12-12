#pragma once
#include "SolidosRSystem.h"
#include "ParticleSystem.h"
#include "ExplosionForceGenerator.h"
#include "ProjectileTrajectoryGenerator.h"
#include "NormalGenerator.h"
#include "Scene.h"
#include "Player.h"
#include "PatosGenerator.h"

class ProjectileTrajectoryGenerator;
using namespace physx;
class Scene2 : public Scene
{
public:
	Scene2() {};
	Scene2(PxPhysics* gPhysics, PxScene* gScene);
	~Scene2();
	virtual void onCollision(physx::PxRigidActor* actor1, physx::PxRigidActor* actor2);
	virtual void Update(double t);


	/*void createProyectil();*/
	SolidosRSystem* getSolidSys() const { return solidSys; };
	Player* getPlayer() const { return player; };
	void setPlayerPos(PxVec3 vec) {
		player->getPlayer()->getSolido()->setGlobalPose(physx::PxTransform( player->getPlayer()->getSolido()->getGlobalPose().p + vec));
	}
private:
	SolidosRSystem* solidSys;
	ParticleSystem* parSys;
	

	void createScene();
	void creteSuelo(physx::PxGeometry* geo, physx::PxTransform transform, physx::PxMaterial* material, Vector4 color);

	void cretePlayer(physx::PxGeometry* geo, physx::PxTransform transform, physx::PxMaterial* material, Vector4 color);
	
	SolidosEstaticos* suelo;
	Player* player;
	std::vector<SolidosEstaticos*> lago;


};

