#include "ch14.h"

CEArray* creatCEArray(int initialCapacity) {
	CEArray* ces = (CEArray*)malloc(sizeof(CEArray));
	if (ces == NULL) return NULL;
	ces->data = (CE*)malloc(sizeof(CE) * initialCapacity);
	if (ces->data == NULL) {
		free(ces);
		return NULL;
	}
	ces->size = 0;
	ces->capacity = initialCapacity;
	return ces;
}

void freeCEArray(CEArray* ces) {
	if (ces != NULL) {
		if (ces->data != NULL) {
			free(ces->data);
		}
		free(ces);
	}
}

void readCEFile(CEArray* ces, char* fileName) {
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("文件打开失败\n");
	}

	char buffer[64] = { 0 };
	int year = 0;
	int month = 0;
	int day = 0;
	int hour = 0;
	int minutes = 0;
	double second = 0.0;

	while (fgets(buffer, 64, fp)) {
		if (ces->size >= ces->capacity) {
			int newCapacity = ces->capacity * 2;
			CE* newData = (CE*)realloc(ces->data,
				sizeof(CE) * newCapacity);
			ces->data = newData;
			ces->capacity = newCapacity;
		}

		if (sscanf(buffer, "%d %d %d %d %d %lf",
			&year, &month, &day,
			&hour, &minutes, &second) != 6){
			year = 0;
			month = 0;
			day = 0;
			hour = 0;
			minutes = 0;
			second = 0.0;
		} else {
			ces->data[ces->size].year = year;
			ces->data[ces->size].month = month;
			ces->data[ces->size].day = day;
			ces->data[ces->size].hour = hour;
			ces->data[ces->size].minutes = minutes;
			ces->data[ces->size].second  = second;
			ces->size++;
		}
		
	}
}