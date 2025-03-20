#include "ch23.h"

void SAC::calcaulate(IOE ioe, OOE ooe) {
	double a_1 = cos(ooe.phi * PI / 180.0) * cos(ooe.kappa * PI / 180.0) - cos(ooe.phi * PI / 180.0) * sin(ooe.omega * PI / 180.0) * sin(ooe.kappa * PI / 180.0);
	double a_2 = -cos(ooe.phi * PI / 180.0) * sin(ooe.kappa * PI / 180.0) - sin(ooe.phi * PI / 180.0) * sin(ooe.omega * PI / 180.0) * sin(ooe.kappa * PI / 180.0);
	double a_3 = -sin(ooe.phi * PI / 180.0) * cos(ooe.omega * PI / 180.0);
	double b_1 = cos(ooe.omega * PI / 180.0) * sin(ooe.kappa * PI / 180.0);
	double b_2 = cos(ooe.omega * PI / 180.0) * cos(ooe.kappa * PI / 180.0);
	double b_3 = -sin(ooe.omega * PI / 180.0);
	double c_1 = sin(ooe.phi * PI / 180.0) * cos(ooe.kappa * PI / 180.0) + cos(ooe.phi * PI / 180.0) * sin(ooe.omega * PI / 180.0) * sin(ooe.kappa * PI / 180.0);
	double c_2 = -sin(ooe.omega * PI / 180.0) * cos(ooe.kappa * PI / 180.0) + cos(ooe.phi * PI / 180.0) * sin(ooe.omega * PI / 180.0) * sin(ooe.kappa * PI / 180.0);
	double c_3 = cos(ooe.phi * PI / 180.0) * cos(ooe.omega * PI / 180.0);

	this->u = a_1 * ioe.x + a_2 * ioe.y + a_3 * ioe.f;
	this->v = b_1 * ioe.x + b_2 * ioe.y + b_3 * ioe.f;
	this->w = c_1 * ioe.x + c_2 * ioe.y + c_3 * ioe.f;
}

void SAC::print() {
	std::cout << u << ' ' << v << ' ' << w << std::endl;
}