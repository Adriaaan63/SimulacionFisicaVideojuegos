#include "Scene1.h"

Scene1::Scene1(PxPhysics* gPhysics, PxScene* gScene):Scene(gPhysics, gScene), canDrawTray(true)
{
}
Scene1::~Scene1()
{
}
void Scene1::onCollision(physx::PxRigidActor* actor1, physx::PxRigidActor* actor2)
{
	for (auto& p : solidSys->getProyectiles()) {
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
	//Mesa
	solidSys->createSolidoEstatico(gScene, &physx::PxBoxGeometry(25, 1000, 1000), { 0,-1000,0 }, material, Vector4(1.0f,0,0,1));
	//Suelo
	creteSuelo(&physx::PxBoxGeometry(5000, 100, 5000), { 0,-500,0 }, material, Vector4(0.63f, 0.6f, 0.38f, 1));
	//Paredes
	solidSys->createSolidoEstatico(gScene, &physx::PxBoxGeometry(1000, 1200, 5), { -900,0,-1000 }, material, Vector4(0.59f, 0.29f, 0.0f, 1));
	solidSys->createSolidoEstatico(gScene, &physx::PxBoxGeometry(1000, 1200, 5), { -900,0,1000 }, material, Vector4(0.59f, 0.29f, 0.0f, 1));
	solidSys->createSolidoEstatico(gScene, &physx::PxBoxGeometry(5, 1200, 1000), { -1000,0,0 }, material, Vector4(0.83f, 0.6f, 0.38f, 1));
	solidSys->createSolidoEstatico(gScene, &physx::PxBoxGeometry(1000, 5, 1000), { 0,1200,0 }, material, Vector4(0.59f, 0.29f, 0.0f, 1));
	//Piramide
	solidSys->createScene(gScene, gPhysics);
	solidSys->createForceGenerator(new GravityForceGenerator(physx::PxVec3(0, -10, 0)));
}
void Scene1::creteSuelo(physx::PxGeometry* geo, physx::PxTransform transform, physx::PxMaterial* material, Vector4 color)
{
	//suelo = new SolidosEstaticos(gScene, geo, transform, material, color);
	suelo = solidSys->createSolidoEstatico(gScene, geo, transform, material, color);
	gScene->addActor(*suelo->getSolido());
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
		{ 0, 0, 0 }, 0.2f, material, { 1,1,1,1 }, 5);
	NormalGenerator* generator = new NormalGenerator(s->getPose().p, s->getShape()->getGeometry().sphere().radius , 2, 10, 10, physx::PxVec3(5, 5, 5), physx::PxVec3(2, 2, 2));
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
	for (auto& s : solidSys->getListSolid()) {
		//std::cout << std::to_string(s->getSolido()->getLinearVelocity().normalize())<< std::endl;
		if (s->getSolido()->getLinearVelocity().normalize() <= 0.1f) {
			cambioScene2 = true;
		}
		else cambioScene2 = false;
	}
}

void Scene1::init(ProjectileTrajectoryGenerator*& newTrajectoryGen, int puntosTotales)
{
	parSys = new ParticleSystem();
	solidSys = new SolidosRSystem(10);
	createScene();
	createTrayectoria();
	newTrajectoryGen = trajectoryGen;
}
