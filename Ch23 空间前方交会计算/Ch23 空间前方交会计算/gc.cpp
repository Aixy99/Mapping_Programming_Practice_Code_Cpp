#include "ch23.h"

void GroundCoord::calculate(OOE ooe1, OOE ooe2, SAC sac1, SAC sac2, ProjectionFactor pf) {
	this->X = ooe1.X_s + pf.N_1 * sac1.u;
	this->Y = 0.5 * ((ooe1.Y_s + pf.N_1 * sac1.v) + (ooe2.Y_s + pf.N_2 * sac2.v));
	this->Z = ooe1.Z_s + pf.N_1 * sac1.w;
}

void GroundCoord::print() {
	std::cout << X << ' '
		<< Y << ' '
		<< Z << std::endl;
}