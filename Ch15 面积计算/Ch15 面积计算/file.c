#include "ch15.h"

PointArray* creatPointArray(int initialCapacity) {
	PointArray* points = (PointArray*)malloc(sizeof(PointArray));
	if (points == NULL) return NULL;
	points->data = (Point*)malloc(sizeof(Point) * initialCapacity);
	if (points->data == NULL) {
		free(points);
		return NULL;
	}
	points->size = 0;
	points->capacity = initialCapacity;
	return points;
}

void freePointArray(PointArray* points) {
	if (points != NULL) {
		if (points->data != NULL) {
			return points->data;
		}
		return points;
	}
}

void readPointDataFile(char *fileName, PointArray* points) {
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("File open failure\n");
		return 1;
	}

	char buffer[64];
	char name[20];
	double x;
	double y;

	fgets(buffer, 64, fp); // skip title
	while (fgets(buffer, 64, fp)) {
		if (points->size >= points->capacity) {
			int newCapacity = points->capacity * 2;
			Point* newData = (Point*)realloc(points->data,
				sizeof(Point) * newCapacity);
			if (newData == NULL) {
				printf("À©ÈÝÊ§°Ü\n");
				return;
			}
			points->data = newData;
			points->capacity = newCapacity;
		}

		if (sscanf(buffer, "%[^,],%lf,%lf",
			name, &x, &y) != 3) {
			printf("ÐÐ¸ñÊ½´íÎó£º%s\n", buffer);
			memcpy(name, " ", 4);
			x = 0;
			y = 0;
		} else {
			memcpy(points->data[points->size].name, name, 4);
			points->data[points->size].x = x;
			points->data[points->size].y = y;
			points->size++;
		}
	}
}