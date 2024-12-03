#include "ParticleGenerator.h"
#include "ParticleSystem.h"
#include "SolidosRSystem.h"
ParticleGenerator::ParticleGenerator(physx::PxVec3 pos, float posMax, float posMin) : pos(pos), posMax(posMax), posMin(posMin) {
}
ParticleGenerator::~ParticleGenerator(){

}
void ParticleGenerator::update(double t, ParticleSystem* prSys) {
	prSys->addParticle(generateParticle());

}
void ParticleGenerator::updateSolid(double t, SolidosRSystem* prSys) {
    SolidoRigido* s = generateSolidoRigido();
    if(s != nullptr)
        prSys->addSolido(s);

}
physx::PxVec3 ParticleGenerator::calculatePosicion() {
    static std::default_random_engine generator;
    std::uniform_real_distribution<float> distributionX(pos.x - posMin, pos.x + posMax);
    std::uniform_real_distribution<float> distributionY(pos.y - posMin, pos.y + posMax);
    std::uniform_real_distribution<float> distributionZ(pos.z - posMin, pos.z + posMax);

    // Generar las coordenadas aleatorias
    float randomX = distributionX(generator);
    float randomY = distributionY(generator);
    float randomZ = distributionZ(generator);

    // Retornar la nueva posición aleatoria
    return physx::PxVec3(randomX, randomY, randomZ);
}




