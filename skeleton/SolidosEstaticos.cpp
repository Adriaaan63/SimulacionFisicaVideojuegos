#include "SolidosEstaticos.h"
SolidosEstaticos::SolidosEstaticos(physx::PxScene* sc, physx::PxGeometry* geo,
    physx::PxTransform transform, physx::PxMaterial* material) : 
    Solidos(sc, geo, transform, material)
{
    newSolid = gScene->getPhysics().createRigidStatic(transform);
    newSolid->attachShape(*shape);
    renderItem = new RenderItem(shape, newSolid, { 0.8,0.8,0.8,1 });
}
SolidosEstaticos::SolidosEstaticos(SolidosEstaticos& const p) {
    *this = p;
}

