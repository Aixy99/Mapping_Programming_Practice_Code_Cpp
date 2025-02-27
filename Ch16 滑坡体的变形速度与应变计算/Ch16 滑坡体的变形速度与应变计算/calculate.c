#include "ch16.h"

double getTwoPointDistance(Coord c1, Coord c2) {
	double distance = sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2)) * 1000.0;
	return distance;
}

double getSpeed(Coord c1, Coord c2) {
	double speed = getTwoPointDistance(c1, c2) / 5.0;
	return speed;
}

void printSpeed(MonitoringData* data) {
	printf("--------监测点位的变形速度--------\n");
	for (int i = 0; i < data->totalPoints; i++) {
		printf("%s", data->points[i].name);
		for (int j = 0; j < data->points[i].totalPeriods - 1; j++) {
			printf(",%.2lf", data->points[i].speed[j]);
		}
		printf("\n");
	}
}

void findMaxSpeed(MonitoringData* data, int* maxSpeedPoint, int* maxindex) {
	double max = data->points[0].speed[0];
	maxSpeedPoint = 0;
	maxindex = 0;
	for (int i = 0; i < data->totalPoints; i++) {
		for (int j = 0; j < data->points[i].totalPeriods - 1; j++) {
			if (max > data->points[i].speed[j]) {
				max = data->points[i].speed[j];
				maxSpeedPoint = i;
				maxindex = j;
			}
		}
	}
}

void printMaxSpeed(MonitoringData* data) {
	int maxSpeedPoint = 0;
	int maxindex = 0;
	findMaxSpeed(data, maxSpeedPoint, maxindex);
	printf("--------最大变形发生点位及发生时段--------\n");
	printf("%s,%d--%d\n", data->points[maxSpeedPoint].name, maxindex + 1, maxindex + 2);
}


void calSpeed(MonitoringData* data) {
	for (int i = 0; i < data->totalPoints; i++) {
		for (int j = 0; j < data->points[i].totalPeriods - 1; j++) {
			data->points[i].speed[j] = getSpeed(data->points[i].coordData[j], data->points[i].coordData[j + 1]);
		}
	}
	printSpeed(data);
	printMaxSpeed(data);
}

void getTwoPointStrain(MonitoringData* data, double* strain, int a, int b) {
	double epsilon, sl, slp1; // S_l, S_l+1
	epsilon = 0.0;
	sl = 0.0;
	slp1 = 0.0;

	for (int i = 0; i < data->totalPoints - 1; i++) {
		sl = getTwoPointDistance(data->points[a].coordData[i], data->points[b].coordData[i]);
		slp1 = getTwoPointDistance(data->points[a].coordData[i + 1], data->points[b].coordData[i + 1]);
		epsilon = (slp1 - sl) / sl;
		strain[i] = epsilon;
	}
}

void printStrain(MonitoringData* data, double* strain, int a, int b) {
	printf("%s-%s", data->points[a].name, data->points[b].name);
	for (int i = 0; i < data->totalPoints - 1; i++) {
		printf(",%.8lf", strain[i]);
	}
	printf("\n");
}

void calStrain(MonitoringData* data) {
	double* strain = (double*)malloc(sizeof(double) * data->totalPoints - 1);
	printf("--------相邻点组的应变--------\n");

	getTwoPointStrain(data, strain, 0, 1);
	printStrain(data, strain, 0, 1);
	getTwoPointStrain(data, strain, 2, 3);
	printStrain(data, strain, 2, 3);

	free(strain);
}