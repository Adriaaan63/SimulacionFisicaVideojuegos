#include "SpringForceGenerator.h"
SpringForceGenerator::SpringForceGenerator(double k, double resting_lenght, Particle* other) : 
	ForceGenerator(), _k(k), _resting_lenght(resting_lenght), _other(other) {

}

physx::PxVec3 SpringForceGenerator::calculateForce(Particle* p) {
	Vector3 relative_pos_vector = _other->getPose().p - p->getPose().p;
	Vector3 force;

	const float leght = relative_pos_vector.normalize();
	const float delta_x = leght - _resting_lenght;

	force = relative_pos_vector * delta_x * _k;
	return force;
}