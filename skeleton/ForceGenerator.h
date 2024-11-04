#pragma once
class ParticleSystem;
#include "Particle.h"
class ForceGenerator {
public:
    ForceGenerator() {};
    virtual physx::PxVec3 calculateForce(Particle* p) = 0;

    virtual ~ForceGenerator() {}
};

