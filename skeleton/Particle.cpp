#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel):vel(Vel), pose(Pos) {
}
Particle::~Particle(){
	if (renderItem != nullptr) {
		DeregisterRenderItem(renderItem);

		delete renderItem;
	}
}
void Particle::integrate(double t) {
	pose.p += vel * t;

	renderItem->transform = &pose;
}