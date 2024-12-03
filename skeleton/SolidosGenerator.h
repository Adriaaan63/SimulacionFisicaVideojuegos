#pragma once
#include "ParticleGenerator.h"
class SolidosGenerator : public ParticleGenerator
{
private:
	
	physx::PxScene* sc;
public:
	SolidosGenerator(physx::PxVec3 pos, float posMax, float posMin, int maxSolidos, physx::PxScene* sc);
	~SolidosGenerator() {};
	Particle* generateParticle() override;
	SolidoRigido* generateSolidoRigido() override;
	
};

