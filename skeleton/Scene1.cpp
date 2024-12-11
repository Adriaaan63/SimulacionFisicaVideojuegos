#include "Scene1.h"

Scene1::Scene1(PxPhysics* gPhysics, PxScene* gScene):gPhysics(gPhysics), gScene(gScene), canDrawTray(true)
{
	parSys = new ParticleSystem();
	solidSys = new SolidosRSystem(10);
	createScene();
	createTrayectoria();
}
Scene1::~Scene1()
{
	delete parSys;
	delete solidSys;
}
void Scene1::onCollision(physx::PxRigidActor* actor1, physx::PxRigidActor* actor2)
{
	for (auto p : solidSys->getProyectiles()) {
		if (p->getSolido() == actor1 || p->getSolido() == actor2) {

			parSys->setExplosion(true);
			for (auto p : p->getParticleGenerator()->getParticulasGenerador()) {
				p->setVel({ 0,0,0 });
			}
			parSys->createForceGenerator(new ExplosionForceGenerator(p->getSolido()->getGlobalPose().p, 150.0f, 1000000.0f, 1.0f));

			p->setTimeLife(-1);

		}
	}
}

void Scene1::createScene()
{
	physx::PxMaterial* material = gPhysics->createMaterial(0.5f, 0.5f, 0.5f); // Fricci�n y restituci�n
	solidSys->createSolidoEstatico(gScene, &physx::PxBoxGeometry(25, 1000, 5000), { 0,-1000,0 }, material);
	solidSys->createScene(gScene, gPhysics);
}

void Scene1::createTrayectoria() {
	// Obtener la posici�n y velocidad del proyectil desde la c�mara
	physx::PxVec3 initialPos = GetCamera()->getTransform().p;
	physx::PxVec3 initialVel = GetCamera()->getDir() * 200;

	// Crear un generador de trayectoria
	trajectoryGen = new ProjectileTrajectoryGenerator(initialPos, initialVel, 0.1f, 5.0f, parSys);

	// Generar y visualizar la trayectoria
	trajectoryGen->generateTrajectory();

}

void Scene1::createProyectil() {
	trajectoryGen->clearTrajectory();
	physx::PxMaterial* material = gPhysics->createMaterial(0.5f, 0.5f, 0.5f);
	SolidoRigido* s = new SolidoRigido(gScene, &physx::PxSphereGeometry(8),
		GetCamera()->getTransform(), GetCamera()->getDir() * 200,
		{ 0, 0, 0 }, 0.2f, material, 5);
	ParticleGenerator* generator = new NormalGenerator(s->getPose().p, s->getShape()->getGeometry().sphere().radius * 10, 2, 10, 10, physx::PxVec3(5, 5, 5), physx::PxVec3(2, 2, 2));
	s->setParticleGenerator(generator);
	solidSys->addProyecyiles(s);
	parSys->createGenerator(generator, 0.01, { 0,0,1,1 });

	gScene->addActor(*s->getSolido());
}

void Scene1::Update(double t) {
	if (solidSys->getProyectiles().size() >= 1) {
		canDrawTray = false;
	}
	else {
		canDrawTray = true;
	}
	parSys->update(t);
	solidSys->update(t);
}