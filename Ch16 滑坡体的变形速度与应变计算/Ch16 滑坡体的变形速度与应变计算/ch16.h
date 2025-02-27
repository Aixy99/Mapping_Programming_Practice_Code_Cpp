#ifndef CH16_H
#define Ch16_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NAME_SIZE 20

typedef struct {
	int num;
	double x;
	double y;
} Coord;

typedef struct {
	char name[NAME_SIZE];
	int totalPeriods; // 总期数
	Coord* coordData;
	double* speed; // 形变速度
} MonitoringPoint;

typedef struct {
	int totalPoints; // 监测点总数
	MonitoringPoint* points;
} MonitoringData;

MonitoringData* readMonitorDataFile(char* fileName);
void printData(const MonitoringData* data);
void freeMonitoringData(MonitoringData* data);
void calSpeed(MonitoringData* data);
void calStrain(MonitoringData* data);
#endif // !CH16_H
