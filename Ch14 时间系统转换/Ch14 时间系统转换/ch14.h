#ifndef CH14_H
#define CH14_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>


typedef struct {
	int year;
	int month;
	int day;
	int hour;
	int minutes;
	double second;
} CE;

typedef struct {
	CE* data;
	int size;
	int capacity;
} CEArray;

double ce2jd(CE ce);
CEArray* creatCEArray(int initialCapacity);
void freeCEArray(CEArray* ces);
void readCEFile(CEArray* ces, char* fileName);
void printCE(CEArray* ces);
void printJD(CEArray* ces);
int ce2doy(CE ce);
void printDoy(CEArray* ces);
void printFish(CEArray* ces);
#endif // !CH14_H

