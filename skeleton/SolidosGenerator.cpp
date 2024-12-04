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
    
    float staticFriction = Random(0.1f, 1.0f); // Fricci�n est�tica entre 0.1 y 1.0
    float dynamicFriction = Random(0.1f, 1.0f); // Fricci�n din�mica entre 0.1 y 1.0
    float restitution = Random(0.0f, 1.0f); // Restituci�n entre 0.0 (inel�stico) y 1.0 (perfectamente el�stico)

    physx::PxMaterial* material = sc->getPhysics().createMaterial(staticFriction, dynamicFriction, restitution);

    // Crear la geometr�a y el s�lido r�gido
    SolidoRigido* s = new SolidoRigido(sc,
        &physx::PxBoxGeometry(1, 1, 1),
        physx::PxTransform(Vector3(0, Random(pos.y - 50, pos.y + 50), 0)),
        { 0, 5, 0 },
        { 0, 0, 0 },
        Random(0.2f, 0.4f), material);


    // Configurar el s�lido en la escena
    s->setSolidoInScene();
    return s;
}
