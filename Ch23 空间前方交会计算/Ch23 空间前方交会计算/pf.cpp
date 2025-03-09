#include "ch23.h"

void ProjectionFactor::calculate(OOE ooe1, OOE ooe2, SAC sac1, SAC sac2) {
	double B_U = ooe2.X_s - ooe1.X_s;
	double B_V = ooe2.Y_s - ooe1.Y_s;
	double B_W = ooe2.Z_s - ooe1.Z_s;

	this->N_1 = (B_U * sac2.w - B_W * sac2.u) / (sac1.u * sac2.w - sac2.u * sac1.w);
	this->N_2 = (B_U * sac1.w - B_W * sac1.u) / (sac1.u * sac2.w - sac2.u * sac1.w);
}

void ProjectionFactor::print() {
	std::cout << N_1 << ' ' << N_2 << std::endl;
}