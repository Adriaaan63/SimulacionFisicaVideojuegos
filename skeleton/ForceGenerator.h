#pragma once
class ParticleSystem;
class SolidosRSystem;
#include "Particle.h"
#include "SolidoRigido.h"
class ForceGenerator {
public:
    ForceGenerator(float duration = 0): duration(duration), alive(true) {};
    virtual physx::PxVec3 calculateForce(Particle* p) = 0;
    virtual physx::PxVec3 calculateForceSolid(SolidoRigido* p) = 0;


    virtual ~ForceGenerator() {}
    bool isAlive() { return alive; };
    virtual void update(double t, ParticleSystem* prSys) {};
    virtual void updateSolido(double t, SolidosRSystem* sSys) {};
protected:
    float duration;
    bool alive;
};

