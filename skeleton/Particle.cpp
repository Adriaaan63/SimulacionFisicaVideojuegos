#include "Particle.h"

Particle::Particle(physx::PxVec3 Pos, physx::PxVec3 Vel, physx::PxVec3 Acc, double Damping):vel(Vel), pose(Pos), acc(Acc), damping(Damping), initialPos(pose), radius(0) {
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(0.1)), &pose, Vector4(1, 1, 0, 1));
	
}
Particle::Particle(Particle* modelParticle) : pose(modelParticle->pose), acc(modelParticle->acc), damping(modelParticle->damping), initialPos(modelParticle->initialPos), radius(0) {
	renderItem = modelParticle->renderItem;
}
Particle::~Particle(){
	if (renderItem != nullptr) {
		DeregisterRenderItem(renderItem);

		delete renderItem;
	}
}
void Particle::integrate(double t) {
	pose.p += vel * t;
	vel += acc * t;
	vel *= pow(damping, t);
}

bool Particle::isOutOfArea() const {
	float distance = (pose.p - initialPos.p).magnitude();  
	return distance > radius;
}