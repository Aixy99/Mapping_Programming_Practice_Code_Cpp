#include "Ch11.h"



double computeH(PosArray* arr, Pos p, int n) {
	computeDistance(arr, p);

	double h = 0.0;
	double up = 0.0; // 分子
	double down = 0.0; // 分母
	//showPosArray(*arr);
	printf("%s 插值列表: ", p.pointName);
	for (int i = 0; i < n; i++) {
		up += arr->data[i].h * (1.0 / arr->data[i].distance);
		down += 1.0 / arr->data[i].distance;
		printf("%s ", arr->data[i].pointName);
	}
	printf("\n\n");
	h = up / down;
	return h;
}