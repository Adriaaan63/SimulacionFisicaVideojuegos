#pragma once
#include "ParticleGenerator.h"
class NormalGenerator : public ParticleGenerator
{
private:
	float radius;
	physx::PxVec3 velMedia;
	physx::PxVec3 desv;
public:
	NormalGenerator(physx::PxVec3 pos, float radius, physx::PxVec3 desV) :ParticleGenerator(pos), velMedia(particleModel->getVel()), desv(desV) {};
	~NormalGenerator() {};
	Particle* generateParticle() override {
		std::normal_distribution<float> distX(velMedia.x, desv.x);
		std::normal_distribution<float> distY(velMedia.y, desv.y);
		std::normal_distribution<float> distZ(velMedia.z, desv.z);

		Vector3 newVel(distX(random_engine), distY(random_engine), distZ(random_engine));
		Particle* p = new Particle(particleModel);
		p->setVel(physx::PxVec3(newVel));
		p->setRadius(radius);
		return p;
	}
};

