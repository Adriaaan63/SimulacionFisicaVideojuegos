#include "Scene2.h"

Scene2::Scene2(PxPhysics* gPhysics, PxScene* gScene) :Scene(gPhysics, gScene)
{
	parSys = new ParticleSystem();
	solidSys = new SolidosRSystem(10);
	createScene();
}
Scene2::~Scene2()
{
	delete parSys;
	delete solidSys;
}
void Scene2::onCollision(physx::PxRigidActor* actor1, physx::PxRigidActor* actor2)
{
	/*for (auto& p : solidSys->getProyectiles()) {
		if (p->getSolido() == actor1 || p->getSolido() == actor2) {

			parSys->setExplosion(true);
			for (auto p : p->getParticleGenerator()->getParticulasGenerador()) {
				p->setVel({ 0,0,0 });
			}
			parSys->createForceGenerator(new ExplosionForceGenerator(p->getSolido()->getGlobalPose().p, 150.0f, 1000000.0f, 1.0f));

			p->setTimeLife(-1);

		}
	}*/
}

void Scene2::createScene()
{
	physx::PxMaterial* material = gPhysics->createMaterial(0.5f, 0.5f, 0.5f); // Fricción y restitución
	lago.push_back( solidSys->createSolidoEstatico(gScene, &physx::PxBoxGeometry(75, 3, 250), { -150,0,0 }, material, Vector4(0.0f, 1.0f, 1.0f, 1),false));
	lago.push_back(solidSys->createSolidoEstatico(gScene, &physx::PxBoxGeometry(75, 3, 250), { 150,0,0 }, material, Vector4(0.0f, 1.0f, 1.0f, 1),false));
	lago.push_back(solidSys->createSolidoEstatico(gScene, &physx::PxBoxGeometry(225, 3, 75), { 0,0,-250 }, material, Vector4(0.0f, 1.0f, 1.0f, 1),false));
	lago.push_back(solidSys->createSolidoEstatico(gScene, &physx::PxBoxGeometry(225, 3, 75), { 0,0,250 }, material, Vector4(0.0f, 1.0f, 1.0f, 1),false));
	
	cretePlayer(&PxBoxGeometry(Vector3(2, 2, 2)), PxTransform(0, 200, 0), material, { 0,0,0,1.0f });
	solidSys->createGeneratorSolids(new PatosGenerator(PxVec3(0, 0, 0), 2000.0f, 2000.0f,10, gScene, lago));
	//creteSuelo(gScene, &physx::PxBoxGeometry(5000, 100, 5000), { 0,-500,0 }, material, Vector4(0.63f, 0.6f, 0.38f, 1));
	//solidSys->createScene(gScene, gPhysics);
	solidSys->generateBuoyancyFG();

	//physx::PxVec3 minCorner = Vector3(-250, -50, -175);
	//physx::PxVec3 maxCorner = Vector3(-75, 50, 325);
	solidSys->createForceGenerator(new WindGenerator(physx::PxVec3(0, 0, -10), 10, 0, Vector3(-250, -50, -225), Vector3(-75, 50, 325)));
	solidSys->createForceGenerator(new WindGenerator(physx::PxVec3(10, 0, 0), 10, 0, Vector3(-250, -50, -325), Vector3(150, 50, -175)));
	solidSys->createForceGenerator(new WindGenerator(physx::PxVec3(0, 0, 10), 10, 0, Vector3(75, -50, -325), Vector3(250, 50, 225)));
	solidSys->createForceGenerator(new WindGenerator(physx::PxVec3(-10, 0, 0), 10, 0, Vector3(-150, -50, 175), Vector3(250, 50, 325)));
	//minCorner = Vector3(-75, -50, 175);
	//maxCorner = Vector3(250, 50, 325);
	//// Calcula el centro de la caja y sus dimensiones
	//physx::PxVec3 boxCenter = (minCorner + maxCorner) * 0.5f;
	//physx::PxVec3 boxHalfExtents = (maxCorner - minCorner) * 0.5f;
	//solidSys->createSolidoEstatico(gScene, &physx::PxBoxGeometry(boxHalfExtents.abs()), PxTransform(boxCenter), material, Vector4(0.0f, 1.0f, 1.0f, 1), false);


}
void Scene2::creteSuelo(physx::PxGeometry* geo, physx::PxTransform transform, physx::PxMaterial* material, Vector4 color)
{
	suelo = new SolidosEstaticos(gScene, geo, transform, material, color);
	gScene->addActor(*suelo->getSolido());
}
void Scene2::cretePlayer(physx::PxGeometry* geo, physx::PxTransform transform, physx::PxMaterial* material, Vector4 color)
{
	SolidoRigido* _playerSolido = new SolidoRigido(gScene, &PxBoxGeometry(Vector3(5, 5, 5)), transform, PxVec3(0, 0, 0), PxVec3(0, 0, 0),0.1f, material,color, (float)INT_MAX);
	player = new Player(_playerSolido);
	//gScene->addActor(*player->getPlayer()->getSolido());
}
//void Scene2::createTrayectoria() {
//	// Obtener la posición y velocidad del proyectil desde la cámara
//	physx::PxVec3 initialPos = GetCamera()->getTransform().p;
//	physx::PxVec3 initialVel = GetCamera()->getDir() * 200;
//
//	// Crear un generador de trayectoria
//	trajectoryGen = new ProjectileTrajectoryGenerator(initialPos, initialVel, 0.1f, 5.0f, parSys);
//
//	// Generar y visualizar la trayectoria
//	trajectoryGen->generateTrajectory();
//
//}

//void Scene2::createProyectil() {
//	trajectoryGen->clearTrajectory();
//	physx::PxMaterial* material = gPhysics->createMaterial(0.5f, 0.5f, 0.5f);
//	SolidoRigido* s = new SolidoRigido(gScene, &physx::PxSphereGeometry(8),
//		GetCamera()->getTransform(), GetCamera()->getDir() * 200,
//		{ 0, 0, 0 }, 0.2f, material, 5);
//	ParticleGenerator* generator = new NormalGenerator(s->getPose().p, s->getShape()->getGeometry().sphere().radius, 2, 10, 10, physx::PxVec3(5, 5, 5), physx::PxVec3(2, 2, 2));
//	s->setParticleGenerator(generator);
//	solidSys->addProyecyiles(s);
//	parSys->createGenerator(generator, 0.01, { 0,0,1,1 });
//
//	gScene->addActor(*s->getSolido());
//	solidSys->setTiros();
//}

void Scene2::Update(double t) {

	/*if (solidSys->getProyectiles().size() >= 1) {
		canDrawTray = false;
	}
	else {
		canDrawTray = true;
	}*/
	parSys->update(t);
	solidSys->update(t);
}

