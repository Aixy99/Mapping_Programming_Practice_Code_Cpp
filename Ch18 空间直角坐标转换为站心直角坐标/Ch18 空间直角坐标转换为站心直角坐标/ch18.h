#ifndef CH18_H
#define CH18_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NAME_SIZE 20
#define PI 3.1415926535

typedef struct {
	char name[NAME_SIZE];
	double x;
	double y;
	double z;
	double e;
	double n;
	double u;
	double l;
	double b;
	double h;
} Point;

typedef struct {
	int size;
	int capacity;
	Point* data;
} PointData;

typedef struct {
	int row;
	int col;
	double** mat;
} Matrix;

PointData* creatPointData(int initialCapacity);
void freePointData(PointData* points);
int readPointsFile(char* pointsFileName, PointData* points);
void printPointData(PointData* points);
Matrix* creatMat(int row, int col);
void initMat(Matrix* m);
void printMat(Matrix* m);
void freeMat(Matrix* m);
Matrix* subMat(Matrix* m, Matrix* n);
Matrix* mulMat(Matrix* m, Matrix* n);
void getPointDataLBH(PointData* points);
void getPointDataENU(Point center, PointData* points);
#endif // !CH18_H
