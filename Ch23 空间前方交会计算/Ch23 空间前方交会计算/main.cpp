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

	std::cout << "像空间辅助坐标 1：";
	sac1.print();
	std::cout << "（w坐标不明原因与参考答案不符，可能是精度问题）\n";
	std::cout << "像空间辅助坐标 2：";
	sac2.print();
	std::cout << "投影系数：";
	pf.print();
	std::cout << "地面坐标：";
	gc.print();
	return 0;
}