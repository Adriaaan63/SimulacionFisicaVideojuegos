#include "PatosGenerator.h"

PatosGenerator::PatosGenerator(physx::PxVec3 pos, float posMax, float posMin, int maxPatos, physx::PxScene* sc, const std::vector<SolidosEstaticos*>& lagos)
    : ParticleGenerator(pos, posMax, posMin), sc(sc), lagos(lagos), maxPatos(maxPatos)
{
    
}

Particle* PatosGenerator::generateParticle()
{
    return nullptr;
}

SolidoRigido* PatosGenerator::generateSolidoRigido()
{

    if (lagos.empty()) return nullptr;

    // Seleccionar aleatoriamente un lago (sólido estático) como delimitador
    int index = Random(0, static_cast<int>(lagos.size()) - 1);
    physx::PxVec3 minBounds, maxBounds;

    // Obtener los límites del sólido estático
    lagos[index]->getBounds(minBounds, maxBounds);

    // Generar posición aleatoria dentro de los límites del lago seleccionado
    physx::PxVec3 randomPos(
        Random(minBounds.x + 20, maxBounds.x - 20),
        8,
        Random(minBounds.z + 20, maxBounds.z - 20));

    //// Configurar material con propiedades aleatorias
    //float staticFriction = Random(0.1f, 0.5f); // Baja fricción para "patos"
    //float dynamicFriction = Random(0.1f, 0.5f);
    //float restitution = Random(0.4f, 0.8f); // Más rebote para "patos"

    float staticFriction = 0; // Baja fricción para "patos"
    float dynamicFriction = 0;
    float restitution = 0; // Más rebote para "patos"

    physx::PxMaterial* material = sc->getPhysics().createMaterial(staticFriction, dynamicFriction, restitution);

    // Crear la geometría y el sólido rígido (patos)
    SolidoRigido* pato = new SolidoRigido(sc,
        &physx::PxBoxGeometry(4, 4, 4),
        physx::PxTransform(randomPos),
        physx::PxVec3(Random(-5.0f, 5.0f), Random(2.0f, 8.0f), Random(-5.0f, 5.0f)),
        physx::PxVec3(0, 0, 0),
        Random(0.1f, 0.3f), material, { 1.0f, 1.0f, 0.0f, 1.0f }, INT_MAX);

    // Configurar el "pato" en la escena
    pato->setSolidoInScene(pato->getSolido());

    return pato;
}
