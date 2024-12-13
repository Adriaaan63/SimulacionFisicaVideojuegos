#include "WindGenerator.h"

WindGenerator::WindGenerator(const physx::PxVec3& velocidad, float k1, float k2, physx::PxVec3 minCorner, physx::PxVec3 maxCorner)
    : ForceGenerator(INT_MAX), velocidad(velocidad), k1(k1), k2(k2), minCorner(minCorner), maxCorner(maxCorner) {
    
    
}
WindGenerator::WindGenerator(const Vector3& velocidad, float k1, float k2, physx::PxVec3 centro, float radio) :ForceGenerator(INT_MAX), velocidad(velocidad), k1(k1), k2(k2), centro(centro), radio(radio) {

};
// Helper function to check if a point is inside the rectangular area
bool isInsideRectangle(const physx::PxVec3& point, const physx::PxVec3& minCorner, const physx::PxVec3& maxCorner) {
    return (point.x >= minCorner.x && point.x <= maxCorner.x &&
            point.y >= minCorner.y && point.y <= maxCorner.y &&
            point.z >= minCorner.z && point.z <= maxCorner.z);
}

physx::PxVec3 WindGenerator::calculateForce(Particle* p) {
    if (radio > 0) {
        if ((p->getPose().p - centro).magnitude() <= radio) {
            // Aplicar la fuerza de viento solo si está dentro del volumen
            calculateVel(p);
            return k1 * (velocidad - p->getVel()) + k2 * (velocidad - p->getVel()).magnitude() * (velocidad - p->getVel());
        }
    }

    else if (isInsideRectangle(p->getPose().p, minCorner, maxCorner)) {
        // Apply wind force only if the particle is within the rectangular area
        calculateVel(p);
        return k1 * (velocidad - p->getVel()) + k2 * (velocidad - p->getVel()).magnitude() * (velocidad - p->getVel());
    }
    return physx::PxVec3(0, 0, 0);
}

physx::PxVec3 WindGenerator::calculateForceSolid(SolidoRigido* p) {
    if (radio > 0) {
        if ((p->getSolido()->getGlobalPose().p - centro).magnitude() <= radio) {
            // Aplicar la fuerza de viento solo si está dentro del volumen
            calculateVelSolid(p);
            return k1 * (velocidad - p->getSolido()->getLinearVelocity()) + k2 * (velocidad - p->getSolido()->getLinearVelocity()).magnitude() * (velocidad - p->getSolido()->getLinearVelocity());
        }
    }
    else if (isInsideRectangle(p->getSolido()->getGlobalPose().p, minCorner, maxCorner)) {
        // Apply wind force only if the rigid body is within the rectangular area
        calculateVelSolid(p);
        return k1 * (velocidad - p->getSolido()->getLinearVelocity()) + k2 * (velocidad - p->getSolido()->getLinearVelocity()).magnitude() * (velocidad - p->getSolido()->getLinearVelocity());
    }
    return physx::PxVec3(0, 0, 0);
}
