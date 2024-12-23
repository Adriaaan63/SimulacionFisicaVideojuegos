#include "SolidosRSystem.h"
#include "ParticleSystem.h"

SolidosRSystem::SolidosRSystem(int maxSolidos, int tiros):Systems(), maxSolidos(maxSolidos), numSolidos(0), tiros (tiros) {
	activeExplosion = false;
}
SolidosRSystem::~SolidosRSystem() {
	for (auto& p : solidos) {
		if (p != nullptr) {
			delete p;
			p = nullptr;
		}
	}

	solidos.clear();
	for (auto& p : proyectiles) {
		if (p != nullptr) {
			delete p;
			p = nullptr;
		}
	}
	proyectiles.clear();
	for (auto& p : solidosEstaticos) {
		if (p != nullptr) {
			delete p;
			p = nullptr;
		}
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
	updateObjets(t);
	updateProyectiles(t);

}
void SolidosRSystem::updateObjets(double t) {
	auto it = solidos.begin();
	while (it != solidos.end()) {
		if ((*it)->isAlive()) {
			applyForces(*it);
			(*it)->integrate(t);
			++it;
		}
		else {
			if ((*it)->getPuntos() != 0) {
				puntos += (*it)->getPuntos();
			}
			auto aux = it;
			++it;
			delete* aux;
			solidos.erase(aux);
			numSolidos--;
			
			
		}
	}
}
void SolidosRSystem::updateProyectiles(double t) {
	auto it = proyectiles.begin();
	while (it != proyectiles.end()) {
		if ((*it)->isAlive()) {
			if ((*it)->getParticleGenerator() != nullptr) {
				for (auto& p : (*it)->getParticleGenerator()->getParticulasGenerador()) {
					if (p != nullptr) {
						p->setVel((*it)->getSolido()->getLinearVelocity());
						p->setInitalPose((*it)->getSolido()->getGlobalPose());
					}
					else {
						std::cout << "No existe \n";
					}
					
				}
			}
			
			applyForces(*it);
			(*it)->integrate(t);
			++it;
		}
		else {
			setTiros();
			if ((*it)->getParticleGenerator() != nullptr)
				(*it)->getParticleGenerator()->setLife(false);
			auto aux = it;
			++it;
			delete* aux;
			proyectiles.erase(aux);
			numSolidos--;
			
		}
	}
}
void SolidosRSystem::addSolido(SolidoRigido* p) {
	numSolidos++;
	solidos.push_back(p);
}
void SolidosRSystem::addProyecyiles(SolidoRigido* p) {
	proyectiles.push_back(p);
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
SolidosEstaticos* SolidosRSystem::createSolidoEstatico(physx::PxScene* gScene, physx::PxGeometry* geo, physx::PxTransform transform, physx::PxMaterial* material, Vector4 color, bool actor)
{
	SolidosEstaticos* newsolidoEstatico = new SolidosEstaticos(gScene, geo, transform, material, color);
	solidosEstaticos.push_back(newsolidoEstatico);

	if(actor)
		gScene->addActor(*newsolidoEstatico->getSolido());
	return newsolidoEstatico;

}
void SolidosRSystem::createScene(physx::PxScene* gScene, physx::PxPhysics* gPhysics)
{
	physx::PxMaterial* material = gPhysics->createMaterial(0, 0.5f, 0.5f); // Fricci�n y restituci�n
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
void SolidosRSystem::generateBuoyancyFG() {
	//SolidoRigido* p4 = new SolidoRigido(, &PxBoxGeometry(Vector3(5, 5, 5)), transform, PxVec3(0, 0, 0), PxVec3(0, 0, 0), 0.1f, material, color, (float)INT_MAX);;
	/*Particle* p4 = new Particle({ -10.0,20.0,0.0 }, { 0.0,0.0,0.0 }, Vector4(1, 1, 1, 1), 60.0f, { 0.0,0.0,0.0 }, 0.85);*/
	//p4->setMass();
	f4 = new BuoyancyForceGenerator(1, 1, 1000.0, { 0.0,5.0,0.0 });
	forceGenerators.push_back(f4);
	//solidos.push_back(p4);
}
