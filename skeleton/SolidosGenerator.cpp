#include "SolidosGenerator.h"

SolidosGenerator::SolidosGenerator(physx::PxVec3 pos, float posMax, float posMin, int maxSolidos, physx::PxScene* sc) :
    ParticleGenerator(pos, posMax, posMin), sc(sc)
{
}

Particle* SolidosGenerator::generateParticle()
{
    return nullptr;
}

SolidoRigido* SolidosGenerator::generateSolidoRigido()
{
    
    float staticFriction = Random(0.1f, 1.0f); // Fricción estática entre 0.1 y 1.0
    float dynamicFriction = Random(0.1f, 1.0f); // Fricción dinámica entre 0.1 y 1.0
    float restitution = Random(0.0f, 1.0f); // Restitución entre 0.0 (inelástico) y 1.0 (perfectamente elástico)

    physx::PxMaterial* material = sc->getPhysics().createMaterial(staticFriction, dynamicFriction, restitution);

    // Crear la geometría y el sólido rígido
    SolidoRigido* s = new SolidoRigido(sc,
        &physx::PxBoxGeometry(1, 1, 1),
        physx::PxTransform(Vector3(0, Random(pos.y - 50, pos.y + 50), 0)),
        { 0, 5, 0 },
        { 0, 0, 0 },
        Random(0.2f, 0.4f), material);


    // Configurar el sólido en la escena
    s->setSolidoInScene();
    return s;
}
