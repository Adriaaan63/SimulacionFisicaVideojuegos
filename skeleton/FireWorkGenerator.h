#pragma once
#include "ParticleGenerator.h"
#include <vector>
class FireWorkGenerator: public ParticleGenerator
{
private:
	int particle_count;
    physx::PxVec3 vel;
    int count = 0;
public:
	FireWorkGenerator(physx::PxVec3 pose, physx::PxVec3 vel, float posMax, float posMin, int count)
		: ParticleGenerator(pose, posMax, posMin), vel(vel), particle_count(count) {
        pos = { Random(-200,200),Random(-200,200),Random(-200,200) };
	}
    virtual ~FireWorkGenerator() {}
    Particle* generateParticle() override {
        Vector3 new_pos = calculatePosicion();
        float vel_mod = vel.magnitude();
        if (count < particle_count) {
            particleModel.setTam({ 2,2,2 });
            Particle* new_particle = new Particle(particleModel);
            new_particle->setInitalPose(physx::PxTransform(pos));
            new_particle->setPose(physx::PxTransform(new_pos));
            static std::default_random_engine random_engine;
            std::uniform_real_distribution<float> speed_distribution(-vel_mod, vel_mod);
            Vector3 random_velocity(
                speed_distribution(random_engine),
                speed_distribution(random_engine),
                speed_distribution(random_engine)
            );
            new_particle->setVel(random_velocity.getNormalized() * vel.magnitude());
            new_particle->setRadius(10000);
            new_particle->getRenderItem()->color = Vector4(Random(0.8, 1), Random(0.0, 1), 0, 0);
            new_particle->setTimeLife(2);
            count++;
            return new_particle;
        }
        isLife = false;
        return nullptr;
    }
    SolidoRigido* generateSolidoRigido() override { return nullptr; };
};

