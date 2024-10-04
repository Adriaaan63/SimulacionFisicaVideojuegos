#include "Proyectil.h"
Proyectil::Proyectil(physx::PxVec3 Pos, physx::PxVec3 VelS, physx::PxVec3 Acc, float masaR, physx::PxVec3 VelR):
	Particle(Pos, VelS, Acc, 0.99),
	mr(masaR),
	vr(VelR), 
	ms(0) {}
Proyectil::~Proyectil() {

}

void Proyectil::ajustarMasa() {
	ms = (mr * vr.magnitudeSquared()) / getVel().magnitudeSquared();
}
void Proyectil::ajustarGravedad(float gravedad) {
	gs = gravedad * (getVel().magnitudeSquared() / vr.magnitudeSquared());
}