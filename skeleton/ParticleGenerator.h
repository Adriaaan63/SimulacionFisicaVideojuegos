#pragma once
#include "PxPhysics.h"
#include "Particle.h"
#include "SolidoRigido.h"
class ParticleSystem;
class SolidosRSystem;
#include <random>
const float GRAVITY = -9.8f;
class ParticleGenerator
{
public:
	ParticleGenerator(physx::PxVec3 pos, float posMax, float posMin);
	virtual ~ParticleGenerator();

	void update(double t, ParticleSystem* prSys);
	void updateSolid(double t, SolidosRSystem* prSys);
	virtual Particle* generateParticle() = 0;
	physx::PxVec3 getPose() const {
		return pos;
	}
	void setModel(Particle newParticleModel) {
		particleModel = newParticleModel;
	}
	physx::PxVec3 calculatePosicion();
	virtual SolidoRigido* generateSolidoRigido() = 0;
	float Random(float min, float max) {
		static std::random_device rd;
		static std::mt19937 gen(rd());
		std::uniform_real_distribution<float>distrib(min, max);
		return distrib(gen);
	}
protected:
	physx::PxVec3 pos;
	Particle particleModel;
	float posMax;
	float posMin;
};

