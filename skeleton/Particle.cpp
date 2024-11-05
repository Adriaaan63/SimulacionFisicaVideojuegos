#include "Particle.h"
#include <iostream>

Particle::Particle(physx::PxVec3 Pos, physx::PxVec3 Vel, Vector4 color, physx::PxVec3 Acc, double Damping, float mass_, physx::PxVec3 force):
	vel(Vel), pose(physx::PxTransform(Pos)), acc(Acc),
	damping(Damping), initialPos(pose), radius(0), 
	mass(mass_), force(force),color(color) {
	createRenderItem();
	
}

Particle::Particle(physx::PxVec3 Pos, physx::PxVec3 Vel, Vector4 color, float mass_,physx::PxVec3 acc, physx::PxVec3 force):
	vel(Vel), pose(physx::PxTransform(Pos)), acc(acc), 
	initialPos(Pos), radius(0), 
	mass(mass_), force(force), color(color)
{
	createRenderItem();
	damping = 0.99;
}
Particle::Particle(Particle&const p) {
	*this = p;
}
Particle::~Particle(){
	if(renderItem != nullptr)
		DeregisterRenderItem(renderItem);
}
void Particle::createRenderItem() {
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1));
	renderItem = new RenderItem(shape, &pose,color);
}
void Particle::integrate(double t) {
	acc = force / mass;
	pose.p += vel * t;
	vel += acc * t;
	
	vel *= pow(damping, t);
	timeLife -= t;
}

bool Particle::isAlive() {
	if (timeLife < 0 || (pose.p - initialPos.p).magnitudeSquared() > pow(radius, 2))
		return false;
	else
	{
		return true;
	}
}