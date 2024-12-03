#pragma once
#include <list>
#include "SolidoRigido.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringFG.h"
#include "BuoyancyForceGenerator.h"
#include <iostream>
#include "Systems.h"
class SolidosRSystem: public Systems
{
protected:
	std::list<SolidoRigido*> solidos;
	int maxSolidos;
	int numSolidos;
	/*std::list<ParticleGenerator*> generators;
	std::list<ForceGenerator*> forceGenerators;*/
public:
	SolidosRSystem(int maxSolidos);
	~SolidosRSystem();

	virtual void update(double t);
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

	void applyForces(SolidoRigido* p);

	void setExplosion(bool active) { activeExplosion = active; };

	/*void setKSpringFG(double newK) {
		f3->setK(f3->getK() + newK);
		std::cout << f3->getK() << std::endl;
	}
	BuoyancyForceGenerator* getFgFlot() const { return f4; };*/
private:
	bool activeExplosion;
	/*AnchoredSpringFG* f3;
	BuoyancyForceGenerator* f4;*/
};


