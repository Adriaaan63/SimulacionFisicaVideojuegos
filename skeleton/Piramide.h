#pragma once
#include "PxPhysics.h"
#include "geometry/PxBoxGeometry.h"
class SolidosRSystem;
class Piramide {
private:
    SolidosRSystem* sistemaSolidos;
    physx::PxScene* gScene;
    physx::PxMaterial* material;

    float baseWidth;     // Ancho de la base de la pir�mide
    float blockSize;     // Tama�o de cada bloque
    float separation;    // Separaci�n entre bloques

public:
    Piramide(physx::PxScene* gScene, SolidosRSystem* sistemaSolidos, physx::PxMaterial* material, float baseWidth, float blockSize, float separation)
        : gScene(gScene),sistemaSolidos(sistemaSolidos), material(material), baseWidth(baseWidth), blockSize(blockSize), separation(separation) {
    }

    ~Piramide() {
        
    }

    void createPiramide();

    /*void update(double t) {
        sistemaSolidos->update(t);
    }*/
};
