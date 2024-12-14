// Scene.cpp
#include "Scene.h"

Scene::Scene(PxPhysics* gPhysics, PxScene* gScene)
    : gPhysics(gPhysics), gScene(gScene), solidSys(nullptr), parSys(nullptr) {
}

Scene::~Scene() {
    cleanUp();
}


void Scene::cleanUp() {
    // Liberar sistemas de partículas y sólidos rígidos
    if (solidSys) {
        delete solidSys;
        solidSys = nullptr;
    }

    if (parSys) {
        delete parSys;
        parSys = nullptr;
    }

    // Aquí puedes añadir cualquier limpieza adicional de la escena
}
