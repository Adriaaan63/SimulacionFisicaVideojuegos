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
	for (auto e : particles) {
		e->integrate(t);
	}
	//for (auto it = particles.begin(); it != particles.end();++it ) {
	//	// Verificar si la partícula sale del área circular
	//	/*if ((*it)->isOutOfArea()) {
	//		delete* it;
	//		auto aux = it;
	//		++aux;
	//		particles.erase(it);
	//		it = aux;
	//	}
	//	else*/
	//	(*it)->integrate(t);
	//	
	//}
	
}
void ParticleSystem::addParticle(Particle* p) {
	particles.push_back(p);
}