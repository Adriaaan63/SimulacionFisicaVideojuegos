#include "Solidos.h"

Solidos::Solidos(physx::PxScene* gScene, physx::PxGeometry* geo, physx::PxTransform transform, physx::PxMaterial* material):
	gScene(gScene), pose(transform)
{
	shape = CreateShape(*geo, material);
}
