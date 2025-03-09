#include "ch23.h"

void SAC::calcaulate(IOE ioe, OOE ooe) {
	double a_1 = cos(ooe.phi / 360.0 * 2.0 * PI) * cos(ooe.kappa/ 360.0 * 2.0 * PI) - cos(ooe.phi / 360.0 * 2.0 * PI) * sin(ooe.omega/ 360.0 * 2.0 * PI) * sin(ooe.kappa/ 360.0 * 2.0 * PI);
	double a_2 = -cos(ooe.phi / 360.0 * 2.0 * PI) * sin(ooe.kappa/ 360.0 * 2.0 * PI) - sin(ooe.phi / 360.0 * 2.0 * PI) * sin(ooe.omega/ 360.0 * 2.0 * PI) * sin(ooe.kappa/ 360.0 * 2.0 * PI);
	double a_3 = -sin(ooe.phi / 360.0 * 2.0 * PI) * cos(ooe.omega/ 360.0 * 2.0 * PI);
	double b_1 = cos(ooe.omega/ 360.0 * 2.0 * PI) * sin(ooe.kappa/ 360.0 * 2.0 * PI);
	double b_2 = cos(ooe.omega/ 360.0 * 2.0 * PI) * cos(ooe.kappa/ 360.0 * 2.0 * PI);
	double b_3 = -sin(ooe.omega/ 360.0 * 2.0 * PI);
	double c_1 = sin(ooe.phi / 360.0 * 2.0 * PI) * cos(ooe.kappa/ 360.0 * 2.0 * PI) + cos(ooe.phi / 360.0 * 2.0 * PI) * sin(ooe.omega/ 360.0 * 2.0 * PI) * sin(ooe.kappa/ 360.0 * 2.0 * PI);
	double c_2 = -sin(ooe.omega/ 360.0 * 2.0 * PI) * cos(ooe.kappa/ 360.0 * 2.0 * PI) + cos(ooe.phi / 360.0 * 2.0 * PI) * sin(ooe.omega/ 360.0 * 2.0 * PI) * sin(ooe.kappa/ 360.0 * 2.0 * PI);
	double c_3 = cos(ooe.phi / 360.0 * 2.0 * PI) * cos(ooe.omega/ 360.0 * 2.0 * PI);

	this->u = a_1 * ioe.x + a_2 * ioe.y + a_3 * ioe.f;
	this->v = b_1 * ioe.x + b_2 * ioe.y + b_3 * ioe.f;
	this->w = c_1 * ioe.x + c_2 * ioe.y + c_3 * ioe.f;
}

void SAC::print() {
	std::cout << u << ' ' << v << ' ' << w << std::endl;
}