#ifndef CH15_H
#define CH15_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
	char name[4];
	double x;
	double y;
} Point;

typedef struct {
	Point* data;
	int size;
	int capacity;
} PointArray;

typedef struct {
	Point a;
	Point b;
	Point c;
	double sideA;	// ±ß³¤
	double sideB;
	double sideC;
	double area;
} Triangle;


PointArray* creatPointArray(int initialCapacity);
void freePointArray(PointArray* points);
void readPointDataFile(char* fileName, PointArray* points);
Triangle creatTriangle(char* a, char* b, char* c, PointArray* points);
#endif // !CH15_H
