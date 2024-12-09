#include "SolidoRigido.h"
SolidoRigido::SolidoRigido(physx::PxScene* sc, physx::PxGeometry* geo, 
    physx::PxTransform transform, physx::PxVec3 linVel, physx::PxVec3 angVel, 
    float mass, physx::PxMaterial* material, float time) : Solidos(sc,geo,transform,material),
 timeLife(time)
{
	newSolid = gScene->getPhysics().createRigidDynamic(transform);
	newSolid->setLinearVelocity(linVel);
	newSolid->setAngularVelocity(angVel);
	newSolid->attachShape(*shape);
	Vector3 inertiaTensor = calculateInertiaTensor(mass);
	newSolid->setMassSpaceInertiaTensor(inertiaTensor);
	newSolid->setMass(mass);
	renderItem = new RenderItem(shape, newSolid, { 0.8,0.8,0.8,1 });
}
SolidoRigido::SolidoRigido(SolidoRigido& const p) {
	*this = p;
}
physx::PxVec3 SolidoRigido::calculateInertiaTensor(float mass)
{
    physx::PxGeometryType::Enum gType = shape->getGeometryType();

    switch (gType)
    {
    case physx::PxGeometryType::eBOX: {
        physx::PxBoxGeometry boxGeometry;
        shape->getBoxGeometry(boxGeometry);
        float hx = 2 * boxGeometry.halfExtents.x;
        float hy = 2 * boxGeometry.halfExtents.y;
        float hz = 2 * boxGeometry.halfExtents.z;

        float Ixx = (1.0f / 12.0f) * mass * (hy * hy + hz * hz);
        float Iyy = (1.0f / 12.0f) * mass * (hx * hx + hz * hz);
        float Izz = (1.0f / 12.0f) * mass * (hx * hx + hy * hy);
        return physx::PxVec3(Ixx, Iyy, Izz);
    }
    case physx::PxGeometryType::eSPHERE: {
        //Dando por hecho que es una esfera solida
        physx::PxSphereGeometry sphereGeometry;
        shape->getSphereGeometry(sphereGeometry);
        float radius = sphereGeometry.radius;

        float I = (2.0f / 5.0f) * mass * radius * radius;
        return physx::PxVec3(I, I, I);
    }
    case physx::PxGeometryType::eCAPSULE: {
        physx::PxCapsuleGeometry capsuleGeometry;
        shape->getCapsuleGeometry(capsuleGeometry);
        float radius = capsuleGeometry.radius;
        float halfHeight = capsuleGeometry.halfHeight;

        float Ixx = (1.0f / 12.0f) * mass * (3 * radius * radius + 4 * halfHeight * halfHeight);
        float Izz = Ixx;
        float Iyy = (1.0f / 2.0f) * mass * radius * radius;
        return physx::PxVec3(Ixx, Iyy, Izz);
    }
    default:
        // Si no se reconoce la geometría, retornar valores por defecto.
        return physx::PxVec3(1.0f, 1.0f, 1.0f);
    }
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
