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

	std::cout << "��ռ丨������ 1��";
	sac1.print();
	std::cout << "��w���겻��ԭ����ο��𰸲����������Ǿ������⣩\n";
	std::cout << "��ռ丨������ 2��";
	sac2.print();
	std::cout << "ͶӰϵ����";
	pf.print();
	std::cout << "�������꣺";
	gc.print();
	return 0;
}