#pragma once
#include "Solidos.h"
class SolidosEstaticos: public Solidos
{
private:
	physx::PxRigidStatic* newSolid;
public:
	SolidosEstaticos() {};
	SolidosEstaticos(physx::PxScene* gScene, physx::PxGeometry* geo,
		physx::PxTransform transform, physx::PxMaterial* material, Vector4 color);
	SolidosEstaticos(SolidosEstaticos& const s);
	SolidosEstaticos& operator=(const SolidosEstaticos& p) {
		newSolid = p.newSolid;
		shape = p.shape;
		gScene = p.gScene;
		return *this;
	}
	~SolidosEstaticos() {
		newSolid->release();
	};
	physx::PxVec3 calculateInertiaTensor(float mass);
	physx::PxRigidStatic* getSolido() const {
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
	bool isAlive();
	void integrate(double t);

};

