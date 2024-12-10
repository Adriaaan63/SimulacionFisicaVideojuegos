#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "PxPhysics.h"
#include "geometry/PxGeometry.h"
#include "Solidos.h"
class ParticleGenerator;
using namespace physx;
class SolidoRigido: public Solidos
{
private:
	physx::PxRigidDynamic* newSolid;
	float timeLife;
	ParticleGenerator* particleGenerator = nullptr; // Generador asociado
public:
	SolidoRigido() {};
	SolidoRigido(physx::PxScene* gScene,physx::PxGeometry* geo,physx::PxTransform transform,
		physx::PxVec3 linVel, physx::PxVec3 angVel, float mass, physx::PxMaterial* material, float time = 20);
	SolidoRigido(SolidoRigido& const s);
	SolidoRigido& operator=(const SolidoRigido& p) {
		newSolid = p.newSolid;
		shape = p.shape;
		gScene = p.gScene;
		return *this;
	}
	SolidoRigido(PxScene* scene, PxGeometry* geometry, PxTransform pose, PxVec3 vel, PxVec3 acc,
		float masa, PxMaterial* material, ParticleGenerator* generator = nullptr);

	~SolidoRigido() {
		newSolid->release();
	};
	physx::PxVec3 calculateInertiaTensor(float mass);
	physx::PxRigidDynamic* getSolido() const {
		return newSolid;
	}
	void setUpdateSolid(double inercia);
	physx::PxMaterial* getMaterial() const {
		if (shape) { 
			physx::PxMaterial* material = nullptr;
			shape->getMaterials(&material, 1);
			return material;
		}
		return nullptr; 
	}
	void setTimeLife(float newtimeLife) { timeLife = newtimeLife; };
	float getTimeLife() const { return timeLife; };
	bool isAlive();
	void integrate(double t);
	ParticleGenerator* getParticleGenerator() { return particleGenerator; }
	void setParticleGenerator(ParticleGenerator* generator) { particleGenerator = generator; }
};

