#include "SolidosRSystem.h"
SolidosRSystem::SolidosRSystem(int maxSolidos):Systems(), maxSolidos(maxSolidos), numSolidos(0) {
	activeExplosion = false;
}
SolidosRSystem::~SolidosRSystem() {
	for (auto p : solidos) {
		delete p;
	}
	solidos.clear();
	for (auto p : solidosEstaticos) {
		delete p;
	}
	solidosEstaticos.clear();
}
void SolidosRSystem::update(double t) {
	if (!activeExplosion) {
		for (auto g : generators) {
			if(numSolidos < maxSolidos)
				g->updateSolid(t, this);
		}
	}

	for (auto fg : forceGenerators) {
		fg->updateSolido(t, this);
	}
	auto it = solidos.begin();
	while (it != solidos.end()) {
		if ((*it)->isAlive()) {
			applyForces(*it);
			(*it)->integrate(t);
			++it;
		}
		else {
			auto aux = it;
			++it;
			delete* aux;
			solidos.erase(aux);
			numSolidos--;
		}
	}

}
void SolidosRSystem::addSolido(SolidoRigido* p) {
	numSolidos++;
	solidos.push_back(p);
}

void SolidosRSystem::applyForces(SolidoRigido* p) {
	physx::PxVec3 totalForce(0, 0, 0);
	auto it = forceGenerators.begin();
	while (it != forceGenerators.end()) {
		if ((*it)->isAlive()) {
			totalForce += (*it)->calculateForceSolid(p);
			++it;
		}
		else {
			auto aux = it;
			++it;
			delete* aux;
			forceGenerators.erase(aux);
		}
	}
	if(totalForce.normalize() > 0)
	p->getSolido()->addForce(totalForce,physx::PxForceMode::eFORCE);
}
void SolidosRSystem::createSolidoEstatico(physx::PxScene* gScene, physx::PxGeometry* geo, physx::PxTransform transform, physx::PxMaterial* material)
{
	SolidosEstaticos* newsolidoEstatico = new SolidosEstaticos(gScene, geo, transform, material);
	solidosEstaticos.push_back(newsolidoEstatico);
	gScene->addActor(*newsolidoEstatico->getSolido());
}
void SolidosRSystem::createScene(physx::PxScene* gScene, physx::PxPhysics* gPhysics)
{
	physx::PxMaterial* material = gPhysics->createMaterial(0.5f, 0.5f, 0.6f); // Fricción y restitución
	Piramide* piramide = new Piramide(gScene,this, material, 250.0f, 25.0f, 10.0f);
	piramide->createPiramide();
}
//void SolidoRigido::generateSpringDemo() {
//	// First one standard spring uniting 2 particles
//	Particle* p1 = new Particle({ -10.0,10.0,0.0 }, { 0.0,0.0,0.0 }, Vector4(1, 1, 1, 1), 60.0f, { 0.0,0.0,0.0 }, 0.85);
//	Particle* p2 = new Particle({ 10.0,10.0,0.0 }, { 0.0,0.0,0.0 }, Vector4(1, 1, 0, 1), 60.0f, { 0.0,0.0,0.0 }, 0.85);
//	p2->setMass(2.5);
//	p1->setMass(2.0);
//	SpringForceGenerator* f1 = new SpringForceGenerator(1, 10, p2);
//	//_force_registry.addRegistry(f1, p1);
//	forceGenerators.push_back(f1);
//	SpringForceGenerator* f2 = new SpringForceGenerator(1, 10, p1);
//	forceGenerators.push_back(f2);
//	particles.push_back(p1);
//	particles.push_back(p2);
//
//
//}
//void ParticleSystem::generateAnchorSpringDemo() {
//	// Then one spring with one fixed side
//	Particle* p3 = new Particle({ -10.0,20.0,0.0 }, { 0.0,0.0,0.0 }, Vector4(1, 1, 1, 1), 60.0f, { 0.0,0.0,0.0 }, 0.85);
//	p3->setMass(2.5);
//	f3 = new AnchoredSpringFG(1, 10, { 10.0,20.0,0.0 });
//	/*_force_registry.addRegistry(f3, p3);*/
//	forceGenerators.push_back(f3);
//	particles.push_back(p3);
//}
//void ParticleSystem::generateBuoyancyFG() {
//	Particle* p4 = new Particle({ -10.0,20.0,0.0 }, { 0,0,0 }, Vector4(1, 1, 1, 1), 60, { 0,0,0 }, 0.85, GeometryType::BOX, { 1,1,1 });
//	/*Particle* p4 = new Particle({ -10.0,20.0,0.0 }, { 0.0,0.0,0.0 }, Vector4(1, 1, 1, 1), 60.0f, { 0.0,0.0,0.0 }, 0.85);*/
//	p4->setMass(75);
//	f4 = new BuoyancyForceGenerator(1, 1, 1000.0, { -10.0,30.0,0.0 });
//	forceGenerators.push_back(f4);
//	particles.push_back(p4);
//}
