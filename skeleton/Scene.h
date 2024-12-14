// Scene.h
#pragma once
#include "RenderUtils.hpp"
#include "SolidosRSystem.h"
#include "ParticleSystem.h"
#include "ProjectileTrajectoryGenerator.h"
using namespace physx;

class Scene {
public:
    Scene() {};
    Scene(PxPhysics* gPhysics, PxScene* gScene);
    virtual ~Scene();
    virtual void onCollision(physx::PxRigidActor* actor1, physx::PxRigidActor* actor2) = 0;
    virtual void Update(double t) = 0;
    virtual void init(ProjectileTrajectoryGenerator*& trajectoryGen) = 0; // Método de inicialización
    virtual void cleanUp(); // Método para liberar recursos
    virtual void createProyectil() = 0;
    SolidosRSystem* getSolidSys() const { return solidSys; };

protected:
    PxPhysics* gPhysics;
    PxScene* gScene;
    SolidosRSystem* solidSys;
    ParticleSystem* parSys;
};
