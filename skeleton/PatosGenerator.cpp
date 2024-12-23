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

    // Seleccionar aleatoriamente un lago (s�lido est�tico) como delimitador
    int index = Random(0, static_cast<int>(lagos.size()) - 1);
    physx::PxVec3 minBounds, maxBounds;

    // Obtener los l�mites del s�lido est�tico
    lagos[index]->getBounds(minBounds, maxBounds);

    // Generar posici�n aleatoria dentro de los l�mites del lago seleccionado
    physx::PxVec3 randomPos(
        Random(minBounds.x + 20, maxBounds.x - 20),
        0,
        Random(minBounds.z + 20, maxBounds.z - 20));

    //// Configurar material con propiedades aleatorias
    //float staticFriction = Random(0.1f, 0.5f); // Baja fricci�n para "patos"
    //float dynamicFriction = Random(0.1f, 0.5f);
    //float restitution = Random(0.4f, 0.8f); // M�s rebote para "patos"

    float staticFriction = 0; // Baja fricci�n para "patos"
    float dynamicFriction = 0;
    float restitution = 0; // M�s rebote para "patos"

    physx::PxMaterial* material = sc->getPhysics().createMaterial(staticFriction, dynamicFriction, restitution);
    int tam = Random(4, 6);
    // Crear la geometr�a y el s�lido r�gido (patos)
    SolidoRigido* pato = new SolidoRigido(sc,
        &physx::PxBoxGeometry(tam, tam, tam),
        physx::PxTransform(randomPos),
        physx::PxVec3(Random(-5.0f, 5.0f), Random(2.0f, 8.0f), Random(-5.0f, 5.0f)),
        physx::PxVec3(0, 0, 0),
        Random(0.07, 0.1), material, { 1.0f, 1.0f, 0.0f, 1.0f }, INT_MAX);

    typeOfPatos(pato);
    // Configurar el "pato" en la escena
    pato->setSolidoInScene(pato->getSolido());

    return pato;
}

void PatosGenerator::typeOfPatos(SolidoRigido* pato)
{
    float mass = pato->getSolido()->getMass();
    if (mass >= 0.08 && mass < 0.09) {
        pato->getRenderItem()->color = { 0.0f, 0.0f,1.0f,1.0f };
        pato->setPuntos(50);
    }
    else if (mass >= 0.09 && mass <= 0.1) {
        pato->getRenderItem()->color = { 1.0f, 0.0f,0.0f,1.0f };
        pato->setPuntos(100);
    }
    else {
        pato->setPuntos(20);
    }
}
