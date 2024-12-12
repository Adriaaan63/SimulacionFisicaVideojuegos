#pragma once
#include "ParticleGenerator.h"
#include "SolidosEstaticos.h"
class PatosGenerator : public ParticleGenerator
{
private:
	int maxPatos;
	physx::PxScene* sc;
	std::vector<SolidosEstaticos*> lagos;
public:
	~PatosGenerator() {};
	PatosGenerator(physx::PxVec3 pos, float posMax, float posMin, int maxPatos, physx::PxScene* sc, const std::vector<SolidosEstaticos*>& lagos);
	Particle* generateParticle() override;
	SolidoRigido* generateSolidoRigido() override;

};

