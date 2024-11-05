#include "WindGenerator.h"
WindGenerator::WindGenerator(const Vector3& velocidad, float k1, float k2, physx::PxVec3 centro, float radio) :ForceGenerator(), velocidad(velocidad), k1(k1), k2(k2), centro(centro), radio(radio) {

};
physx::PxVec3 WindGenerator::calculateForce(Particle* p) {
    if ((p->getPose().p - centro).magnitude() <= radio) {
        // Aplicar la fuerza de viento solo si está dentro del volumen
        return k1 * (velocidad - p->getVel()) + k2 * (velocidad - p->getVel()).magnitude() * (velocidad - p->getVel());
    }
    return physx::PxVec3(0, 0, 0);
}