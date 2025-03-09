#include "ch23.h"
#include <fstream>

bool initData(IOE& ioe1, OOE& ooe1, IOE& ioe2, OOE& ooe2) {
	std::ifstream ifs;
	ifs.open(FILENAME, std::ios::in);
	if(!ifs.is_open()) {
		std::cout << "file {" << FILENAME << "} open failure" << std::endl;
		ifs.close();
		return false;
	}

	ifs >> ooe1.X_s;
	ifs >> ooe1.Y_s;
	ifs >> ooe1.Z_s;
	ifs >> ooe1.phi;
	ifs >> ooe1.omega;
	ifs >> ooe1.kappa;
	ifs >> ioe1.x;
	ifs >> ioe1.y;
	ifs >> ioe1.f;

	ifs >> ooe2.X_s;
	ifs >> ooe2.Y_s;
	ifs >> ooe2.Z_s;
	ifs >> ooe2.phi;
	ifs >> ooe2.omega;
	ifs >> ooe2.kappa;
	ifs >> ioe2.x;
	ifs >> ioe2.y;
	ifs >> ioe2.f;

	return true;
}