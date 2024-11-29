#include "SolidoRigido.h"
SolidoRigido::SolidoRigido(physx::PxPhysics* gPhysics, physx::PxTransform transform, physx::PxVec3 linVel, physx::PxVec3 angVel, physx::PxVec3 tam)
{
	newSolid = gPhysics->createRigidDynamic(transform);
	newSolid->setLinearVelocity(linVel);
	newSolid->setAngularVelocity(angVel);
	physx::PxShape* shape = CreateShape(physx::PxBoxGeometry(tam));
	newSolid->attachShape(*shape);
	physx::PxRigidBodyExt::setMassAndUpdateInertia(*newSolid, 0.15);
	RenderItem* dynamicItem;
	dynamicItem = new RenderItem(shape, newSolid, { 0.8,0.8,0.8,1 });
}