#include "ch18.h"

int main() {
	char* fileName = "../data/XYZ.dat";

	PointData* points = creatPointData(1);
	readPointsFile(fileName, points);
	getPointDataLBH(points);
	// ��һ������Ϊվ��
	getPointDataENU(points->data[6], points);
	printPointData(points);
	freePointData(points);
	return 0;
}