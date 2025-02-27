#include "Ch11.h"

void showPosInfo(Pos p) {
	printf("%s\t%lf\t%lf\t%lf\t%lf\n",
		p.pointName,
		p.x,
		p.y,
		p.h,
		p.distance);
}

void showPosArray(PosArray arr) {
	for (int i = 0; i < arr.size; i++) {
		showPosInfo(arr.data[i]);
	}
}

int main() {
	Pos q[4] = {
		{ "Q1",4310.0,3600.0,0,0 },
		{ "Q2",4330.0,3600.0,0,0 },
		{ "Q3",4310.0,3620.0,0,0 },
		{ "Q4",4330.0,3620.0,0,0 }
	};
	char* posDataFile = "../data/²âÕ¾×ø±ê.txt";
	PosArray* posData = createPosArray(10);

	readPosData(posDataFile, posData);
	int n = 5; // ²åÖµ½×Êý
	for (int i = 0; i < 4; i++) {
		q[i].h = computeH(posData, q[i], n);
	}
	for (int i = 0; i < 4; i++) {
		showPosInfo(q[i]);
	}

	freePosArray(posData);
	return 0;
}