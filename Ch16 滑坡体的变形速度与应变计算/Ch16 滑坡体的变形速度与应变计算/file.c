#include "ch16.h"

MonitoringData* readMonitorDataFile(char* fileName) {
	MonitoringData* data = (MonitoringData*)malloc(sizeof(MonitoringData));
	char buffer[128] = { 0 };

	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		free(data);
		printf("�ļ���ʧ��\n"); return NULL;
	}

	fgets(buffer, 128, fp);
	if (sscanf(buffer, "%d", &data->totalPoints) != 1) {
		data->totalPoints = 0;
	} else {
		data->points = (MonitoringPoint*)malloc(sizeof(MonitoringPoint) * data->totalPoints);
	}
	for (int i = 0; i < data->totalPoints; i++) {
		fgets(buffer, 128, fp);
		char name[NAME_SIZE] = { 0 };
		int totalPeriods = 0;

		if (sscanf(buffer, "%[^,],%d",
			name, &totalPeriods) != 2) {
			strcpy(name, "Unknown");
			totalPeriods = 0;
		}
		strcpy(data->points[i].name, name);
		data->points[i].totalPeriods = totalPeriods;
		data->points[i].speed = (double*)malloc(sizeof(double) * data->points[i].totalPeriods - 1);
		data->points[i].coordData = (Coord*)malloc(sizeof(Coord) * data->points[i].totalPeriods);

		for (int j = 0; j < data->points[i].totalPeriods; j++) {
			fgets(buffer, 128, fp);
			int num = 0;
			double x = 0.0;
			double y = 0.0;
			if (sscanf(buffer, "%d,%lf, %lf",
				&num, &x, &y) != 3) {
				num = 0;
				x = 0.0;
				y = 0.0;
			}
			data->points[i].coordData[j].num = num;
			data->points[i].coordData[j].x = x;
			data->points[i].coordData[j].y = y;
		}
	}
	fclose(fp);
	return data;
}

void freeMonitoringData(MonitoringData* data) {
	if (data != NULL) {
		if (data->points != NULL) {
			for (int i = 0; i < data->totalPoints; i++) {
				if (data->points[i].coordData != NULL) {
					free(data->points[i].coordData);
				}
			}
			free(data->points);
		}
		free(data);
	}
}

void printData(const MonitoringData* data) {
	printf("��������: %d\n", data->totalPoints);
	for (int i = 0; i < data->totalPoints; i++) {
		printf("������: %s, ������: %d\n", data->points[i].name, data->points[i].totalPeriods);
		printf("��������:\n");
		for (int j = 0; j < data->points[i].totalPeriods; j++) {
			printf("���: %d, X: %.4f, Y: %.4f\n",
				data->points[i].coordData[j].num,
				data->points[i].coordData[j].x,
				data->points[i].coordData[j].y);
		}
		printf("--------------------------\n");
	}
}