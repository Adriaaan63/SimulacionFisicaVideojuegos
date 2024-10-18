#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "PxPhysics.h"

class Particle
{
public:
	Particle(physx::PxVec3 Pos, physx::PxVec3 Vel, physx::PxVec3 Acc, double damping);
	Particle(Particle* modelParticle);
	virtual ~Particle();

	virtual void integrate(double t);

	void setRenderItem(RenderItem* newRenderItem) { renderItem = newRenderItem; };
	RenderItem* getRenderItem() const { return renderItem; };

	physx::PxTransform getPose() const { return pose; };

	void Particle::setAcceleration(const physx::PxVec3& newAcc) {
		acc = newAcc;
	}
	physx::PxVec3 getVel() const { return vel; }
	void setVel(physx::PxVec3 newVel) { 
		vel = newVel; 
	}

	bool isOutOfArea() const;

	void setRadius(float newradius) { radius = newradius; };
	float getradius() const { return radius; };
	physx::PxVec3 getAcc() const { return acc; };
	double getDamping() const { return damping; };
protected:
	physx::PxVec3 vel;
	physx::PxVec3 acc;
	physx::PxTransform pose; //A render item le pasaremos la direccion de este pose, para que se actualice automaticamente
	RenderItem* renderItem;
	double damping;
	physx::PxTransform initialPos;
	float radius;
};

