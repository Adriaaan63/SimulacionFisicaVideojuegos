#include "SolidosEstaticos.h"
SolidosEstaticos::SolidosEstaticos(physx::PxScene* sc, physx::PxGeometry* geo,
    physx::PxTransform transform, physx::PxMaterial* material, Vector4 color) : 
    Solidos(sc, geo, transform, material)
{
    newSolid = gScene->getPhysics().createRigidStatic(transform);
    newSolid->attachShape(*shape);
    renderItem = new RenderItem(shape, newSolid, color);
}
SolidosEstaticos::SolidosEstaticos(SolidosEstaticos& const p) {
    *this = p;
}

