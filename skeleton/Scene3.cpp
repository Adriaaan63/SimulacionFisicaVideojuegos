#include "Scene3.h"

Scene3::Scene3(PxPhysics* gPhysics, PxScene* gScene) :Scene(gPhysics, gScene)
{
}
Scene3::~Scene3()
{
}
void Scene3::onCollision(physx::PxRigidActor* actor1, physx::PxRigidActor* actor2)
{
}
void Scene3::Update(double t)
{
	timer += t;
	if (timer > timeToFireWork) {
		createScene();
		timer = 0;
	}
	parSys->update(t);
}
void Scene3::createScene() {
	parSys->createGenerator(new FireWorkGenerator({ 0,0,0 }, { 0,150,0 }, 50, 50, 20), 0.01f, { 1,0,0,1 });
}
void Scene3::init(ProjectileTrajectoryGenerator*& trajectoryGen, int puntosTotales)
{
	parSys = new ParticleSystem();
}
