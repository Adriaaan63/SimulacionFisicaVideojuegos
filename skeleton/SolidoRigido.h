#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "PxPhysics.h"
#include "geometry/PxGeometry.h"
#include "Solidos.h"
class NormalGenerator;
using namespace physx;
class SolidoRigido: public Solidos
{
private:
	physx::PxRigidDynamic* newSolid;
	float timeLife;
	NormalGenerator* particleGenerator = nullptr; // Generador asociado
	int puntos;
public:
	SolidoRigido() {};
	SolidoRigido(physx::PxScene* gScene,physx::PxGeometry* geo,physx::PxTransform transform,
		physx::PxVec3 linVel, physx::PxVec3 angVel, float mass, physx::PxMaterial* material, Vector4 color, float time = 20, int puntos = 0);
	SolidoRigido(SolidoRigido& const s);
	SolidoRigido& operator=(const SolidoRigido& p) {
		newSolid = p.newSolid;
		shape = p.shape;
		gScene = p.gScene;
		return *this;
	}
	SolidoRigido(PxScene* scene, PxGeometry* geometry, PxTransform pose, PxVec3 vel, PxVec3 acc,
		float masa, PxMaterial* material, Vector4 color, NormalGenerator* generator = nullptr);

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
	NormalGenerator* getParticleGenerator() { return particleGenerator; }
	void setParticleGenerator(NormalGenerator* generator) { particleGenerator = generator; }
	void setColorRender(Vector4 color) {
		renderItem->color = color;
	}
	void setPuntos(int newPuntos) { puntos = newPuntos; };
	int getPuntos() const { return puntos; };
};

