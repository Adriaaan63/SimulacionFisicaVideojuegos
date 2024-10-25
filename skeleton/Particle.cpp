#include "Particle.h"
#include <iostream>

Particle::Particle(physx::PxVec3 Pos, physx::PxVec3 Vel, physx::PxVec3 Acc, double Damping):vel(Vel), pose(physx::PxTransform(Pos)), acc(Acc), damping(Damping), initialPos(pose), radius(0) {
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1));
	renderItem = new RenderItem(shape, &pose, Vector4(1, 1, 1, 1));
	
}

Particle::Particle(physx::PxVec3 Pos, physx::PxVec3 Vel, physx::PxVec3 acc): vel(Vel), pose(physx::PxTransform(Pos)), acc(acc), initialPos(Pos), radius(0)
{
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1));
	renderItem = new RenderItem(shape, &pose, Vector4(1, 1, 1, 1));
	damping = 0.99;
}
Particle::Particle(Particle&const p) {
	*this = p;
}
Particle::~Particle(){
	DeregisterRenderItem(renderItem);
}
void Particle::integrate(double t) {
	pose.p += vel * t;
	vel += acc * t;
	
	vel *= pow(damping, t);
	timeLife -= t;
}

bool Particle::isAlive() {
	if (timeLife < 0 || (pose.p - initialPos.p).magnitudeSquared() > pow(radius,2))
		return false;
	else
	{
		return true;
	}
}