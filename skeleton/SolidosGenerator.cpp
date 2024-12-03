#include "SolidosGenerator.h"

SolidosGenerator::SolidosGenerator(physx::PxVec3 pos, float posMax, float posMin, int maxSolidos,physx::PxScene* sc):
    ParticleGenerator(pos,posMax,posMin), sc(sc)
{
}

Particle* SolidosGenerator::generateParticle()
{
	return nullptr;
}
SolidoRigido* SolidosGenerator::generateSolidoRigido()
{
   
        SolidoRigido* s = new SolidoRigido(sc,physx::PxTransform(Vector3(0, Random(pos.y - 50, pos.y +50), 0)), { 0,5,0 }, { 0,0,0 }, { 1,1,1 });
        s->setUpdateSolid(Random(0.0f, 1.0f));
        s->setSolidoInScene();
        return s;
    
   
}