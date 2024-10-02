#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double Damping):vel(Vel), pose(Pos), acc(Acc), damping(Damping) {
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.5)), &pose, Vector4(1, 1, 0, 1));
}
Particle::~Particle(){
	if (renderItem != nullptr) {
		DeregisterRenderItem(renderItem);

		delete renderItem;
	}
}
void Particle::integrate(double t) {
	vel += acc * t;
	vel *= pow(damping, t);
	pose.p += vel * t;

}