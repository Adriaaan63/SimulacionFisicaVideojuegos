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
	void getBounds(physx::PxVec3& minBounds, physx::PxVec3& maxBounds) const {
		if (!newSolid || !shape) {
			minBounds = physx::PxVec3(0);
			maxBounds = physx::PxVec3(0);
			return;
		}

		// Obtener la posici�n del s�lido
		physx::PxTransform transform = newSolid->getGlobalPose();

		// Determinar los l�mites seg�n el tipo de geometr�a
		if (shape->getGeometryType() == physx::PxGeometryType::eBOX) {
			physx::PxBoxGeometry boxGeometry;
			if (shape->getBoxGeometry(boxGeometry)) {
				physx::PxVec3 halfExtents = boxGeometry.halfExtents;
				physx::PxVec3 center = transform.p;
				minBounds = center - halfExtents;
				maxBounds = center + halfExtents;
			}
		}
		// Agrega aqu� otros tipos de geometr�a si es necesario (esferas, c�psulas, etc.)
		else {
			minBounds = transform.p;
			maxBounds = transform.p;
		}
	}

};

