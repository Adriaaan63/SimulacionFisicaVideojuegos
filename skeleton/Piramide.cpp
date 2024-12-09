#include "Piramide.h"
#include "SolidosRSystem.h"
void Piramide::createPiramide() {
    int levels = static_cast<int>(baseWidth / (blockSize + separation));
    float startY = blockSize / 2; // Altura inicial de los bloques
    float offsetX;

    for (int level = 0; level < levels; ++level) {
        int blocksInLevel = levels - level;
        offsetX = -(blocksInLevel - 1) * (blockSize + separation) / 2;

        for (int i = 0; i < blocksInLevel; ++i) {
            physx::PxTransform transform({0, startY,  offsetX + i * (blockSize + separation) }); // Solo en XZ
            physx::PxBoxGeometry geometry(blockSize / 2, blockSize / 2, blockSize / 2);

            auto solid = new SolidoRigido(gScene, &geometry, transform, { 0,5,0 }, { 0,0,0 }, 0.5f, material, INT_MAX);
            gScene->addActor(*solid->getSolido());
            sistemaSolidos->addSolido(solid);
        }

        startY += blockSize; // Elevar la siguiente capa
    }
}