#include "ParticleSystem.h"
ParticleSystem::ParticleSystem() {

}
ParticleSystem::~ParticleSystem() {
	for (auto p : particles) {
		delete p;
	}
	particles.clear();
	for (auto g : generators) {
		delete g;
	}
	generators.clear();
}
void ParticleSystem::update(double t) {
	for (auto g : generators) {
		g->update(t, this);
	}
	auto it = particles.begin();
	while (it != particles.end()) {
		if ((*it)->isAlive()) {
			(*it)->integrate(t);
			++it;
		}
		else {
			auto aux = it;
			++it;
			delete *aux;
			particles.erase(aux);
		}
	}
	
}
void ParticleSystem::addParticle(Particle* p) {
	particles.push_back(p);
}
