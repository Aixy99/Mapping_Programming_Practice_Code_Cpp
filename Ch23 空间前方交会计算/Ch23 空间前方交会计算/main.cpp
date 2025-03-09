#include "ch23.h"

int main() {
	IOE ioe1, ioe2;
	OOE ooe1, ooe2;
	SAC sac1, sac2;
	ProjectionFactor pf;
	GroundCoord gc;
	if(!initData(ioe1, ooe1, ioe2, ooe2)) {
		return -1;
	}

	sac1.calcaulate(ioe1, ooe1);
	sac2.calcaulate(ioe2, ooe2);
	pf.calculate(ooe1, ooe2, sac1, sac2);
	gc.calculate(ooe1, ooe2, sac1, sac2, pf);
	sac1.print();
	sac2.print();
	pf.print();
	gc.print();
	return 0;
}