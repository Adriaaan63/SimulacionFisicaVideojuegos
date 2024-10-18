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
	for (auto it = particles.begin(); it != particles.end(); ) {
		Particle* p = *it;
		p->integrate(t);

		// Verificar si la partícula sale del área circular
		if (p->isOutOfArea()) {
			delete p;
			it = particles.erase(it);
		}
		else {
			++it;
		}
	}
	for (auto& g : generators) {
		particles.push_back(g->generateParticle());
	}
}