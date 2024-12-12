#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>
#include "Vector3D.h"

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Particle.h"
#include <vector>
#include <iostream>
#include "Proyectil.h"
#include "ParticleSystem.h"
#include "NormalGenerator.h"
#include "GravityForceGenerator.h"
#include "TornadoGenerator.h"
#include "WindGenerator.h"
#include "UniformGenerator.h"
#include "ExplosionForceGenerator.h"
#include "SolidosGenerator.h"
#include "SolidoRigido.h"
#include "SolidosRSystem.h"
#include "ProjectileTrajectoryGenerator.h"
#include "Scene1.h"
#include "Scene2.h"

std::string display_text = "This is a test";
std::string display_text1 = "This is a test";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;
RenderItem* obj = NULL;
RenderItem* obj1 = NULL;
RenderItem* obj2 = NULL;
RenderItem* obj3 = NULL;
//std::vector<Particle*> proyectiles;
//ParticleSystem* ParticleSys;
//SolidosRSystem* SolidoSys;
ProjectileTrajectoryGenerator* trajectoryGen;
Scene1* scene1;
Scene2* scene2;


bool canUseCalbacks;
bool canDrawTray;
// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);	
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	PxShape* shape = CreateShape(PxSphereGeometry(1), gMaterial);
	obj = new RenderItem(shape, new PxTransform(0, 0, 0), Vector4(1, 1, 1, 1));
	
	float distanceEje = 15.0f;
	Vector3D<float> ejeX(distanceEje, 0.0f,0.0f);
	PxShape* shape1 = CreateShape(PxSphereGeometry(1), gMaterial);
	obj1 = new RenderItem(shape1, new PxTransform(ejeX.x, ejeX.y, ejeX.z), Vector4(1, 0, 0, 1));

	Vector3D<float> ejeY(0.0f, distanceEje, 0.0f);
	PxShape* shape2 = CreateShape(PxSphereGeometry(1), gMaterial);
	obj2 = new RenderItem(shape2, new PxTransform(ejeY.x, ejeY.y, ejeY.z), Vector4(0, 1, 0, 1));

	Vector3D<float> ejeZ(0.0f, 0.0, distanceEje);
	PxShape* shape3 = CreateShape(PxSphereGeometry(1), gMaterial);
	obj3 = new RenderItem(shape3, new PxTransform(ejeZ.x, ejeZ.y, ejeZ.z), Vector4(0, 0, 1, 1));
	
	/*particle = new Particle(Vector3(0, 0, 0), Vector3(0, 1, 0), Vector3(0,5,0), 0.99);*/
	

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	/*ParticleSys = new ParticleSystem();
	SolidoSys = new SolidosRSystem(10);*/

	
#pragma region Practica
	//------------------------------Practicas----------------------------------------------
	//ParticleSys->generateSpringDemo();
	//ParticleSys->generateAnchorSpringDemo();
	//ParticleSys->generateBuoyancyFG();

	//Viento
	//ParticleSys->createGenerator(new NormalGenerator(physx::PxVec3(0, 0, 0), 2000, 25, 20, 0, physx::PxVec3(5, 5, 5), physx::PxVec3(2, 2, 2)), 0.01, Vector4(1,1,1,1));
	//ParticleSys->createForceGenerator(new WindGenerator(physx::PxVec3(-100, 0, 0), 10, 0, Vector3(0, 100, 0), 70.0f));

	//Torbellino
	//ParticleSys->createGenerator(new NormalGenerator(physx::PxVec3(0, 0, 0), 200, 5, 20, 0, physx::PxVec3(5, 5, 5), physx::PxVec3(2, 2, 2)), 0.01, Vector4(1, 1, 1, 1));
	//ParticleSys->createGenerator(new NormalGenerator(physx::PxVec3(0, 0, 0), 2000, 50, 20, 0, physx::PxVec3(5, 5, 5), physx::PxVec3(2, 2, 2)), 0.05, Vector4(1, 0, 1, 1));
	//ParticleSys->createForceGenerator(new TornadoGenerator(physx::PxVec3(0, 0, 0), 0.25, 0, Vector3(0, 0, 0), 2000.0F, 5.0F));

	//ParticleSys->createGenerator(new NormalGenerator(physx::PxVec3(0, 0, 0), 200, 5, 20, 0, physx::PxVec3(5, 5, 5), physx::PxVec3(2, 2, 2)), 0.25, Vector4(1,0,1,1));
	/*ParticleSys->createGenerator(new UniformGenerator(physx::PxVec3(50, 0, 0), 30, 5, 0, 0, physx::PxVec3(5, 5, 5), physx::PxVec3(10, 10, 10)));
	ParticleSys->createGenerator(new UniformGenerator(physx::PxVec3(-50, 0, 0), 30, 5, 20, 20, physx::PxVec3(-50, -50, -50), physx::PxVec3(50, 50, 50)));*/
	//ParticleSys->createGenerator(new UniformGenerator(physx::PxVec3(0, 0, 0), 100, 5));

	//ParticleSys->createForceGenerator(new GravityForceGenerator(physx::PxVec3(0, -10, 0)));
	//ParticleSys->createForceGenerator(new GravityForceGenerator(physx::PxVec3(0, 10, 0)));

	//SolidosRigidos
	/*PxRigidStatic* suelo = gPhysics->createRigidStatic(PxTransform({ 0,0,0 }));
	PxShape* shape4 = CreateShape(PxBoxGeometry(100, 0.1, 100));
	suelo->attachShape(*shape4);
	gScene->addActor(*suelo);
	RenderItem* item;
	item = new RenderItem(shape4, suelo, { 0.8,0.8,0.8,1 });*/

	/*SolidoRigido* solidoDinamico = new SolidoRigido(gPhysics, { -70,200,-70 }, { 0,5,0 }, { 0,0,0 }, { 5,5,5 });
	gScene->addActor(*solidoDinamico->getSolido());*/
	//SolidoSys->createGeneratorSolids(new SolidosGenerator(physx::PxVec3(-70, 200, -70), 500, 1000, 10, gScene));
	//SolidoSys->createForceGenerator(new GravityForceGenerator(physx::PxVec3(0, -10, 0)));
	//SolidoSys->createForceGenerator(new WindGenerator(physx::PxVec3(-100, 0, 0), 10, 0, Vector3(0, 0, 0), 100.0f));

	//----------------------------------------------------------------------------------------------------------
#pragma endregion

#pragma region Proyecto
	//------------------------------Proyecto----------------------------------------------
	canUseCalbacks = false;
	GetCamera()->setTransform(PxVec3(500.0f, 300.0f, 0.0f), PxVec3(-0.6f, -0.3f, 0.0f));
	GetCamera()->scene = 2;
	scene2 = new Scene2(gPhysics, gScene);
	/*scene1 = new Scene1(gPhysics, gScene);
	trajectoryGen = scene1->getTrayectGen();*/
	//------------------------------------------------------------------------------------
#pragma endregion

	
}
	


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	
	//display_text = "Puntos: " + std::to_string(scene1->getSolidSys()->getPuntos());
	//display_text1 = "Tiros: " + std::to_string(scene1->getSolidSys()->getTiros());

	//scene1->Update(t);
	scene2->Update(t);
	//canDrawTray = scene1->getCanDrawTray();

	gScene->simulate(t);
	gScene->fetchResults(true);
	
	
	
	
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);
	//delete scene1;
	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
	
	//if (particle != nullptr) {
	//	delete particle;  // Esto tambi�n llama al destructor de Particle, que debe liberar el RenderItem.
	//	particle = nullptr;
	//}
	/*for (auto& e : proyectiles) {
		delete e;
	}
	proyectiles.clear();*/
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	/*case 'P':
		if(scene1->getSolidSys()->getTiros() > 0)
			scene1->createProyectil();
		
		break;*/
	case 'W':
		scene2->setPlayerPos(PxVec3(-2,0,0));
		break;
	case 'A':
		scene2->setPlayerPos(PxVec3(0, 0, 2));
		break;
	case 'S':
		scene2->setPlayerPos(PxVec3(2, 0, 0));
		break;
	case 'D':
		scene2->setPlayerPos(PxVec3(0, 0, -2));
		break;
	/*case 'H':
		ParticleSys->setExplosion(true);
		ParticleSys->createForceGenerator(new ExplosionForceGenerator(physx::PxVec3(0,0,0), 150.0f, 1000000.0f, 1.0f));
		break;*/
	/*case 'E':
		ParticleSys->setKSpringFG(50);
		break;
	case 'F':
		ParticleSys->createForceGenerator(new GravityForceGenerator(physx::PxVec3(0, 10, 0), 2.0f));
		break;
	case 'M':
		break;
	case 'V':
		if (ParticleSys->getFgFlot() != nullptr) {
			ParticleSys->getFgFlot()->setVolume(0.1f);
		}
		break;
	case 'B':
		if (ParticleSys->getFgFlot() != nullptr) {
			ParticleSys->getFgFlot()->setVolume(-0.1f);
		}
		break;*/

	default:
		break;
	}
}

void onCollision(physx::PxRigidActor* actor1, physx::PxRigidActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
	//scene1->onCollision(actor1, actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}