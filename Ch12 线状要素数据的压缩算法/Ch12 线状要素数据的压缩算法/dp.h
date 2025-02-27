#ifndef DP_H
#define DP_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define D_T 100

typedef struct {
	int num;
	double x;
	double y;
	double distance;
} Point;

typedef struct {
	Point* data;
	int size;
	int capacity;
} PointArray;

PointArray* creatPointArray(int initialCapacity);
void freePointArray(PointArray* arr);
void readPointData(PointArray* pointData, char* fileName);
void dp(PointArray* pointData, int start, int end);
#endif // !DP_H

