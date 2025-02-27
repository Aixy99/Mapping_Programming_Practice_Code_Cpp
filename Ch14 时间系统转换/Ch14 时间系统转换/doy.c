#include "ch14.h"

int isLeap(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int ce2doy(CE ce) {
	int doy = 0;
	int dom[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (isLeap(ce.year)) {
		dom[1] = 29;
	}
	for (int i = 0; i < ce.month - 1; i++) {
		doy += dom[i];
	}
	doy += ce.day;
	return doy;
}