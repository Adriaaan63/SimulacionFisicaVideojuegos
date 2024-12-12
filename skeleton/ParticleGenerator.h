#pragma once
#include "PxPhysics.h"
#include "Particle.h"
#include "SolidoRigido.h"
class ParticleSystem;
class SolidosRSystem;
#include <random>
#include <list>
const float GRAVITY = -9.8f;
class ParticleGenerator
{
public:
	ParticleGenerator(physx::PxVec3 pos, float posMax, float posMin);
	virtual ~ParticleGenerator();

	void update(double t, ParticleSystem* prSys);
	void updateSolid(double t, SolidosRSystem* prSys);
	void cleanUpParticles();
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
	void setPose(physx::PxTransform newPose) { pos = newPose.p; };
	std::list<Particle*> getParticulasGenerador() const { return particulasGenerador; };

	bool getLive() const { return isLife; };
	void setLife(bool life) { isLife = life; };
protected:
	physx::PxVec3 pos;
	Particle particleModel;
	std::list<Particle*> particulasGenerador;
	float posMax;
	float posMin;
	bool isLife;
};

