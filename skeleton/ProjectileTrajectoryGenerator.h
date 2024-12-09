#pragma once
#include "ParticleGenerator.h"
#include "RenderUtils.hpp"

class ProjectileTrajectoryGenerator : public ParticleGenerator {
public:
    ProjectileTrajectoryGenerator(physx::PxVec3 initialPos, physx::PxVec3 velocity, float timeStep, float maxTime)
        : ParticleGenerator(initialPos, 0, 0), velocity(velocity), timeStep(timeStep), maxTime(maxTime) {
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
    void generateTrajectory() {
        clearTrajectory(); // Eliminar cualquier trayectoria previa.

        float t = 0.0f;
        while (t <= maxTime) {
            // Calcular posición futura
            physx::PxVec3 newPos = calculatePositionAtTime(t);

            // Crear un marcador visual (esfera pequeña) en esta posición
            physx::PxShape* pointShape = CreateShape(physx::PxSphereGeometry(0.3f), nullptr); // Esfera de radio 0.3.
            auto renderItem = new RenderItem(pointShape, new physx::PxTransform(newPos), Vector4(1, 0, 0, 0.8f)); // Semitransparente.
            renderItems.push_back(renderItem);

            t += timeStep; // Avanzar en el tiempo
        }
    }

    // Limpia las bolas anteriores de la escena
    void clearTrajectory() {
        for (auto& item : renderItems) {
            DeregisterRenderItem(item);
        }
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
};
