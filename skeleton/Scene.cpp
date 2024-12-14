// Scene.cpp
#include "Scene.h"

Scene::Scene(PxPhysics* gPhysics, PxScene* gScene)
    : gPhysics(gPhysics), gScene(gScene), solidSys(nullptr), parSys(nullptr) {
}

Scene::~Scene() {
    cleanUp();
}


void Scene::cleanUp() {
    // Liberar sistemas de part�culas y s�lidos r�gidos
    if (solidSys) {
        delete solidSys;
        solidSys = nullptr;
    }

    if (parSys) {
        delete parSys;
        parSys = nullptr;
    }

    // Aqu� puedes a�adir cualquier limpieza adicional de la escena
}
