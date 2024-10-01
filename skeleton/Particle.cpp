#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc):vel(Vel), pose(Pos), acc(Acc) {
}
Particle::~Particle(){
	if (renderItem != nullptr) {
		DeregisterRenderItem(renderItem);

		delete renderItem;
	}
}
void Particle::integrate(double t) {
	vel += acc * t;

	pose.p += vel * t;

	renderItem->transform = &pose;
}