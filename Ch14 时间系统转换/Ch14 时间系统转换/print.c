#include "ch14.h"

void printCE(CEArray* ces) {
	printf("----------公历--------------\n");
	for (int i = 0; i < ces->size; i++) {
		printf("%04d %02d %02d %02d:%02d:%09.6lf\n",
			ces->data[i].year,
			ces->data[i].month,
			ces->data[i].day,
			ces->data[i].hour,
			ces->data[i].minutes,
			ces->data[i].second);
	}
}

void printJD(CEArray* ces) {
	printf("----------JD--------------\n");
	for (int i = 0; i < ces->size; i++) {
		printf("%lf\n", ce2jd(ces->data[i]));
	}
}

void printDoy(CEArray* ces) {
	printf("----------年积日--------------\n");
	for (int i = 0; i < ces->size; i++) {
		printf("%d\n", ce2doy(ces->data[i]));
	}
}

void printFish(CEArray* ces) {
	CE start = { 2016, 1, 1,0,0,0.0 };
	int d = 0;
	printf("----------三天打鱼两天晒网--------------\n");
	for (int i = 0; i < ces->size; i++) {
		printf("%04d %02d %02d ",
			ces->data[i].year,
			ces->data[i].month,
			ces->data[i].day);

		d = ((int)floor(ce2jd(ces->data[i]) - ce2jd(start)) + 1) % 5;
		if (d > 0 && d < 4) {
			printf("打鱼日\n");
		} else {
			printf("晒网日\n");
		}
	}
}