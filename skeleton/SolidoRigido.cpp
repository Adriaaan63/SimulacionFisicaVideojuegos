#include "SolidoRigido.h"
SolidoRigido::SolidoRigido(physx::PxScene* sc, physx::PxTransform transform, physx::PxVec3 linVel, physx::PxVec3 angVel, physx::PxVec3 tam) :gScene(sc), pose(transform),
tam(tam), timeLife(20)
{
	newSolid = gScene->getPhysics().createRigidDynamic(transform);
	newSolid->setLinearVelocity(linVel);
	newSolid->setAngularVelocity(angVel);
	shape = CreateShape(physx::PxBoxGeometry(tam));
	newSolid->attachShape(*shape);
	//physx::PxRigidBodyExt::setMassAndUpdateInertia(*newSolid, 0.15);
	dynamicItem = new RenderItem(shape, newSolid, { 0.8,0.8,0.8,1 });
}
SolidoRigido::SolidoRigido(SolidoRigido& const p) {
	*this = p;
}

void SolidoRigido::setUpdateSolid(double inercia)
{
	physx::PxRigidBodyExt::setMassAndUpdateInertia(*newSolid, inercia);
}
bool SolidoRigido::isAlive() {
	if (timeLife < 0 )
		return false;
	else
	{
		return true;
	}
}
void SolidoRigido::integrate(double t) {
	timeLife -= t;
}
