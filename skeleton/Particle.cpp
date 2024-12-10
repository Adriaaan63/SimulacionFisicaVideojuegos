#include "Particle.h"
#include <iostream>

Particle::Particle(physx::PxVec3 Pos, physx::PxVec3 Vel, Vector4 color, physx::PxVec3 Acc, double Damping, float mass_, physx::PxVec3 force):
	vel(Vel), pose(physx::PxTransform(Pos)), acc(Acc),
	damping(Damping), initialPos(pose), radius(0), 
	mass(mass_), force(force),color(color), tam({ 1,1,1 }) {
	createRenderItem(_type, tam);
	
}

Particle::Particle(physx::PxVec3 Pos, physx::PxVec3 Vel, Vector4 color, float mass_,physx::PxVec3 acc, physx::PxVec3 force):
	vel(Vel), pose(physx::PxTransform(Pos)), acc(acc), 
	initialPos(Pos), radius(0), 
	mass(mass_), force(force), color(color), tam({ 0.1,0.1,0.1 })
{
	createRenderItem(_type,tam);
	damping = 0.99;
}

Particle::Particle(physx::PxVec3 Pos, physx::PxVec3 Vel, Vector4 color, float time_, physx::PxVec3 Acc, double Damping, physx::PxVec3 force) :
	vel(Vel), pose(physx::PxTransform(Pos)), acc(Acc),
	damping(Damping), initialPos(pose), radius(INT_MAX),
	timeLife(time_), force(force), color(color), tam({1,1,1}) {
	
	createRenderItem(_type,tam);

}
Particle::Particle(physx::PxVec3 Pos, physx::PxVec3 Vel, Vector4 color, float time_, physx::PxVec3 Acc, double Damping, physx::PxGeometryType::Enum type, physx::PxVec3 tam, physx::PxVec3 force ):
	vel(Vel), pose(physx::PxTransform(Pos)), acc(Acc),
	damping(Damping), initialPos(pose), radius(50),
	timeLife(time_), force(force), color(color), _type(type), tam(tam) {

	createRenderItem(_type, tam);

}
Particle::Particle(Particle&const p) {
	*this = p;
}
Particle::~Particle(){
	if(renderItem != nullptr)
		DeregisterRenderItem(renderItem);
}
void Particle::createRenderItem(physx::PxGeometryType::Enum type, physx::PxVec3 tam) {
	if (type == physx::PxGeometryType::eSPHERE) {
		physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(tam.x));
		renderItem = new RenderItem(shape, &pose, color);
	}
	else if (type == physx::PxGeometryType::eBOX) {
		physx::PxShape* shape = CreateShape(physx::PxBoxGeometry(tam.x, tam.y,tam.z));
		renderItem = new RenderItem(shape, &pose, color);
	}
	
}
void Particle::integrate(double t) {
	if(force.normalize() != 0)
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