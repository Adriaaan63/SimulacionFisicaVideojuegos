#include "Proyectil.h"
Proyectil::Proyectil(physx::PxVec3 Pos, physx::PxVec3 VelS, physx::PxVec3 Acc, float masaR, physx::PxVec3 VelR):
	Particle(Pos, VelS, Acc, 0.99,0),
	mr(masaR),
	vr(VelR), 
	ms(0),gs(0) {
	ajustarMasa();
	ajustarGravedad(9.8f);
	
}
Proyectil::~Proyectil() {

}

void Proyectil::ajustarMasa() {
	float velSimuladaMagSq = vel.magnitudeSquared();
	float velRealMagSq = vr.magnitudeSquared();

	
	ms = (mr * velRealMagSq) / velSimuladaMagSq;
	
}
void Proyectil::ajustarGravedad(float gravedad) {
	
	float velSimuladaMagSq = vel.magnitudeSquared();
	float velRealMagSq = vr.magnitudeSquared();

	
	gs = gravedad * (velSimuladaMagSq / velRealMagSq);
	
}
void Proyectil::integrate(double t) {
	acc += Vector3(0, -abs(gs), 0);
	Particle::integrate(t);
}