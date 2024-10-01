#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc);
	~Particle();

	void integrate(double t);

	void setRenderItem(RenderItem* newRenderItem) { renderItem = newRenderItem; };
	RenderItem* getRenderItem() const { return renderItem; };

	physx::PxTransform getPose() const { return pose; };

	void Particle::setAcceleration(const Vector3& newAcc) {
		acc = newAcc;
	}

private:
	Vector3 vel;
	Vector3 acc;
	physx::PxTransform pose; //A render item le pasaremos la direccion de este pose, para que se actualice automaticamente
	RenderItem* renderItem;
};

