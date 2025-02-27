#include "dp.h"

int main() {
	char* pointFileName = "../data/原始数据.txt";
	char* outputPointFileName = "../data/结果.txt";

	PointArray* pointData = creatPointArray(10);
	readPointData(pointData, pointFileName);
	int minNum = pointData->data[0].num;
	int maxNum = pointData->data[0].num;
	for (int i = 0; i < pointData->size; i++) {
		if (pointData->data[i].num < minNum) {
			minNum = pointData->data[i].num;
		}
		if (pointData->data[i].num > maxNum) {
			maxNum = pointData->data[i].num;
		}
	}
	printf("min: %d\n", minNum);
	printf("max: %d\n", maxNum);
	dp(pointData, minNum, maxNum);
	FILE* fp = fopen(outputPointFileName, "w");
	for (int i = 0; i < pointData->size; i++) {
		if (pointData->data[i].num == 0) continue;
		fprintf(fp, "%d %lf %lf\n", pointData->data[i].num, pointData->data[i].x, pointData->data[i].y);
	}

	freePointArray(pointData);
	return 0;
}