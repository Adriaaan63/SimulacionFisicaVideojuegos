#pragma once
#include "ParticleGenerator.h"
#include "RenderUtils.hpp"
#include "Particle.h"

class ProjectileTrajectoryGenerator : public ParticleGenerator {
public:
    ProjectileTrajectoryGenerator(physx::PxVec3 initialPos, physx::PxVec3 velocity, float timeStep, float maxTime, ParticleSystem* prSys)
        : ParticleGenerator(initialPos, 0, 0), velocity(velocity), timeStep(timeStep), maxTime(maxTime), prSys(prSys) {
    }

    ~ProjectileTrajectoryGenerator() {
        for (auto& item : renderItems) {
            delete item; // Liberar memoria de los RenderItems.
        }
        renderItems.clear();
    }

    // No generamos partículas ni sólidos, solo trayectorias visuales
    Particle* generateParticle() override { return nullptr; }
    SolidoRigido* generateSolidoRigido() override { return nullptr; }

    // Generar una secuencia de bolas para visualizar la trayectoria
    void generateTrajectory();

    // Limpia las bolas anteriores de la escena
    void clearTrajectory() {
        /*for (auto& item : renderItems) {
            DeregisterRenderItem(item);
        }*/
       
        for (auto& p : particlesTrayec) {
            p->setTimeLife(-1);
        }
        particlesTrayec.clear();
        renderItems.clear();
    }
    // Métodos para actualizar posición y velocidad
    void setPosition(const physx::PxVec3& newPos) { pos = newPos; }
    void setVelocity(const physx::PxVec3& newVelocity) { velocity = newVelocity; }

private:
    // Calcula posición en el tiempo t
    physx::PxVec3 calculatePositionAtTime(float t) {
        physx::PxVec3 gravity(0, GRAVITY, 0);
        return pos + velocity * t + 0.5f * gravity * t * t;
    }

    physx::PxVec3 velocity;   // Velocidad inicial del proyectil
    float timeStep;           // Paso de tiempo para la simulación
    float maxTime;            // Tiempo máximo para la trayectoria
    std::vector<RenderItem*> renderItems; // Almacenar las esferas de la trayectoria
    ParticleSystem* prSys;
    std::vector<Particle*> particlesTrayec;
    int maxParticles = 30;
};
