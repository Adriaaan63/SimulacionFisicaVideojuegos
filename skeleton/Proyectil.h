#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "Particle.h"
class Proyectil: public Particle
{
public:
	Proyectil(physx::PxVec3 Pos, physx::PxVec3 VelS, physx::PxVec3 Acc, float masaR, physx::PxVec3 VelR);
	~Proyectil();

	void ajustarMasa();
	void ajustarGravedad(float gravedad);
private:
	physx::PxVec3 vr;
	float ms, mr, gs;
};

