#include "AnchoredSpringFG.h"
AnchoredSpringFG::AnchoredSpringFG(double k, double resting, const physx::PxVec3& anchor_pos) :
	SpringForceGenerator(k, resting, nullptr) {
	_other = new Particle(anchor_pos, { 0,0,0 }, Vector4(0, 1, 1, 1),60, { 0,0,0 }, 0, GeometryType::BOX);
}
AnchoredSpringFG::~AnchoredSpringFG() {
	delete _other;
}