#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "PxPhysics.h"

enum class GeometryType {
	SPHERE,
	BOX
};
class Particle
{
public:
	Particle() {};
	Particle(physx::PxVec3 Pos, physx::PxVec3 Vel,Vector4 color, physx::PxVec3 Acc, double damping, float mass_, physx::PxVec3 force = { 0,0,0 });
	Particle(physx::PxVec3 Pos, physx::PxVec3 Vel,Vector4 color, float mass_, physx::PxVec3 acc = { 0,0,0 }, physx::PxVec3 force = { 0,0,0 });
	Particle(const Particle& p);
	Particle(physx::PxVec3 Pos, physx::PxVec3 Vel, Vector4 color, float time_, physx::PxVec3 Acc, double Damping, physx::PxVec3 force = { 0,0,0 });
	Particle(physx::PxVec3 Pos, physx::PxVec3 Vel, Vector4 color, float time_, physx::PxVec3 Acc, double Damping, physx::PxGeometryType::Enum type, physx::PxVec3 tam = {1,1,1}, physx::PxVec3 force = {0,0,0});

	virtual ~Particle();

	virtual void integrate(double t);

	void setRenderItem(RenderItem* newRenderItem) { renderItem = newRenderItem; };
	RenderItem* getRenderItem() const { return renderItem; };

	physx::PxTransform getPose() const { return pose; };
	void setPose(physx::PxTransform newPose) { pose= newPose; };
	void setInitalPose(physx::PxTransform newInitialPose) { initialPos= newInitialPose; };

	void Particle::setAcceleration(const physx::PxVec3& newAcc) {
		acc = newAcc;
	}
	physx::PxVec3 getVel() const { return vel; }
	void setVel(physx::PxVec3 newVel) { 
		vel = newVel; 
	}

	bool isAlive();

	void setRadius(float newradius) { radius = newradius; };
	float getradius() const { return radius; };

	void setTimeLife(float newtimeLife) { timeLife = newtimeLife; };
	float getTimeLife() const { return timeLife; };

	physx::PxVec3 getAcc() const { return acc; };

	double getDamping() const { return damping; };
	void setDamping(double damp) { damping = damp; };

	float getMass() const { return mass; }
	void setMass(float newMass) { mass = newMass; }

	// Métodos de fuerza
	void setForce(physx::PxVec3 newforce) {
		force = newforce;
	}

	void createRenderItem(physx::PxGeometryType::Enum type, physx::PxVec3 tam);
	Particle& operator=(const Particle& p) {
		pose = p.pose;
		vel = p.vel;
		acc = p.acc;
		damping = p.damping;
		initialPos = p.initialPos;
		radius = p.radius;
		timeLife = p.timeLife;
		mass = p.mass;
		force = p.force;
		color = p.color;
		createRenderItem(p._type, p.tam);
		
		return *this;
	}
protected:
	physx::PxGeometryType::Enum _type = physx::PxGeometryType::Enum::eSPHERE;
	physx::PxVec3 vel;
	physx::PxVec3 acc;
	physx::PxVec3 force;
	Vector4 color;
	physx::PxTransform pose; //A render item le pasaremos la direccion de este pose, para que se actualice automaticamente
	RenderItem* renderItem;
	double damping;
	physx::PxTransform initialPos;
	float radius;
	float timeLife;
	float mass;
	physx::PxVec3 tam = { 0.5,0.5,0.5 };
};

