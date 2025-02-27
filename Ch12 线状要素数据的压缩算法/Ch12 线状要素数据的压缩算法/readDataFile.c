#include "dp.h"

PointArray* creatPointArray(int initialCapacity) {
	PointArray* arr = (PointArray*)malloc(sizeof(PointArray));
	if (arr == NULL) return NULL;
	arr->data = (Point*)malloc(sizeof(Point) * initialCapacity);
	if (arr->data == NULL) {
		free(arr);
		return NULL;
	}
	arr->size = 0;
	arr->capacity = initialCapacity;
	return arr;
}

void freePointArray(PointArray* arr) {
	if (arr != NULL) {
		if (arr->data != NULL) {
			free(arr->data);
		}
		free(arr);
	}
}

void readPointData(PointArray* pointData, char* fileName) {
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("file open failure: %s\n", fileName);
		return 1;
	}

	char buff[256] = { 0 };
	int num = 0;
	double x = 0.0;
	double y = 0.0;

	while (fgets(buff, 256, fp)) {
		// À©ÈÝ
		if (pointData->size >= pointData->capacity) {
			int newCacpcity = pointData->capacity * 2;
			Point* newData = (Point*)realloc(pointData->data,
				sizeof(Point) * newCacpcity);
			if (newData == NULL) {
				printf("À©ÈÝÊ§°Ü£¬size = %d\n", pointData->size);
				return 2;
			}
			pointData->capacity = newCacpcity;
			pointData->data = newData;
		}

		if (sscanf(buff, "%d,%lf,%lf",
			&num,&x,&y) != 3) {
			printf("ÐÐ¸ñÊ½ÓÐÎó: %s\n", buff);
			num = 0;
			x = 0.0;
			y = 0.0;
		} else {
			pointData->data[pointData->size].num = num;
			pointData->data[pointData->size].x = x;
			pointData->data[pointData->size].y = y;
			pointData->size++;
		}
	}
	fclose(fp);
}