#include "ProjectileTrajectoryGenerator.h"
#include "ParticleSystem.h"

void ProjectileTrajectoryGenerator::generateTrajectory()
{
    clearTrajectory(); // Eliminar cualquier trayectoria previa.

    int i = 0;
    float t = 0.0f;
    while (t <= maxTime && i < maxParticles) {
        // Calcular posición futura
        physx::PxVec3 newPos = calculatePositionAtTime(t);

        Particle* p = new Particle(newPos, physx::PxVec3(0, 0, 0), Vector4(1, 0, 0, 1), INT_MAX, physx::PxVec3(0, 0, 0), 0.9f, physx::PxGeometryType::Enum::eSPHERE, physx::PxVec3(0.3, 0.3, 0.3));
        prSys->addParticle(p);
        particlesTrayec.push_back(p);
        renderItems.push_back(p->getRenderItem());
        i++;

        t += timeStep; // Avanzar en el tiempo
    }
    std::cout << i;
}
