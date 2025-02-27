#include "Ch11.h"

double twoPointDistance(Pos p1, Pos p2) {
	double distance = 0.0;
	distance = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	return distance;
}

void sort(PosArray* arr) {
	for (int i = 0; i < arr->size - 1; i++) {
		for (int j = 0; j < arr->size - 1 - i; j++) {
			if (arr->data[j].distance > arr->data[j + 1].distance) {
				Pos temp = arr->data[j];
				arr->data[j] = arr->data[j + 1];
				arr->data[j + 1] = temp;
			}
		}
	}
}

void computeDistance(PosArray* arr, Pos p) {
	for (int i = 0; i < arr->size; i++) {
		arr->data[i].distance = twoPointDistance(arr->data[i], p);
	}

	sort(arr);
}

