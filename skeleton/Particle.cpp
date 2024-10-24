#include "Particle.h"
#include <iostream>

Particle::Particle(physx::PxVec3 Pos, physx::PxVec3 Vel, physx::PxVec3 Acc, double Damping):vel(Vel), pose(physx::PxTransform(Pos)), acc(Acc), damping(Damping), initialPos(pose), radius(0) {
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(0.1));
	renderItem = new RenderItem(shape, &pose, Vector4(1, 1, 1, 1));
	
}

Particle::Particle(physx::PxVec3 Pos, physx::PxVec3 Vel, physx::PxVec3 acc): vel(Vel), pose(physx::PxTransform(Pos)), acc(acc), initialPos(Pos), radius(0)
{
	
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1)), &pose, Vector4(1, 1, 1, 1));
	damping = 0.99;
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
	std::cout << pose.p.y << std::endl;
}

bool Particle::isOutOfArea() const {
	float distance = (pose.p - initialPos.p).magnitude();  
	return distance > radius;
}