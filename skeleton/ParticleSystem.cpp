#include "ParticleSystem.h"
ParticleSystem::ParticleSystem() {

}
ParticleSystem::~ParticleSystem() {
	for (auto& p : particles) {
		delete p;
	}
	particles.clear();
	for (auto& g : generators) {
		delete g;
	}
	generators.clear();
}
void ParticleSystem::update(double t) {
	for (auto& p : particles) {
		p->integrate(t);

		//Matar particulas por tiempo y si sale de la posicion

	}
}