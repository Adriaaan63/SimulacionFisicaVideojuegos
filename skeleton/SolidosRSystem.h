#pragma once
#include <list>
#include "SolidoRigido.h"
#include "SolidosEstaticos.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringFG.h"
#include "BuoyancyForceGenerator.h"
#include <iostream>
#include "Systems.h"
#include "Piramide.h"
#include "ExplosionForceGenerator.h"
class ParticleSystem;

class SolidosRSystem: public Systems
{
protected:
	std::list<SolidoRigido*> solidos;
	std::list<SolidoRigido*> proyectiles;
	std::list<SolidosEstaticos*> solidosEstaticos;
	int maxSolidos;
	int numSolidos;
	
	/*std::list<ParticleGenerator*> generators;
	std::list<ForceGenerator*> forceGenerators;*/
public:
	SolidosRSystem(int maxSolidos, ParticleSystem* pSys);
	~SolidosRSystem();

	virtual void update(double t);
	void updateObjets(double t);
	void updateProyectiles(double t);
	void createGeneratorSolids(ParticleGenerator* g) {
		generators.push_back(g);
	}
	void createForceGenerator(ForceGenerator* g) {
		forceGenerators.push_back(g);
	}
	/*void generateSpringDemo();
	void generateAnchorSpringDemo();
	void generateBuoyancyFG();*/

	std::list<SolidoRigido*> getListSolid() const { return solidos; };
	void addSolido(SolidoRigido* p);

	void addProyecyiles(SolidoRigido* p);

	void applyForces(SolidoRigido* p);

	void setExplosion(bool active) { activeExplosion = active; };

	/*void setKSpringFG(double newK) {
		f3->setK(f3->getK() + newK);
		std::cout << f3->getK() << std::endl;
	}
	BuoyancyForceGenerator* getFgFlot() const { return f4; };*/

	void createSolidoEstatico(physx::PxScene* gScene, physx::PxGeometry* geo,
		physx::PxTransform transform, physx::PxMaterial* material);
	void createScene(physx::PxScene* gScene, physx::PxPhysics* gPhysics);
	void onCollision(physx::PxRigidActor* actor1, physx::PxRigidActor* actor2);
private:
	bool activeExplosion;
	ParticleSystem* pSys;
	/*AnchoredSpringFG* f3;
	BuoyancyForceGenerator* f4;*/
};


