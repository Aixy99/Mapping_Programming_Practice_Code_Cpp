#ifndef CH01_H
#define CH01_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
	char pointName[10];
	double x;
	double y;
	double h;
	double distance; //到目标点的距离
} Pos;

typedef struct {
	Pos* data;
	int size;
	int capacity;
} PosArray;

int readPosData(char* file, PosArray* posData);
PosArray* createPosArray(int initialCapacity);
void freePosArray(PosArray* posData);
double twoPointDistance(Pos p1, Pos p2);
void computeDistance(PosArray* arr, Pos p);
double computeH(PosArray* arr, Pos p, int n);
void showPosArray(PosArray arr);
#endif // !CH01_H
