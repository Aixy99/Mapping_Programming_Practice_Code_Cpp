#include "ch18.h"
#define MAX_COL 256

PointData* creatPointData(int initialCapacity) {
	PointData* points = (PointData*)malloc(sizeof(PointData));
	if (!points) return NULL;
	points->data = (Point*)malloc(sizeof(Point) * initialCapacity);
	if (!points->data) {
		free(points);
		return NULL;
	}

	points->size = 0;
	points->capacity = initialCapacity;
	return points;
}

void freePointData(PointData* points) {
	if (points) {
		if (points->data) {
			free(points->data);
			points->data = NULL;
		}
		free(points);
	}
}

void printPointData(PointData* points) {
	printf("-------------------XYZ-------------------\n");
	for (int i = 0; i < points->size; i++) {
		printf("%s %.4lf %.4lf %.4lf\n",
			points->data[i].name,
			points->data[i].x,
			points->data[i].y,
			points->data[i].z);
	}
	printf("-------------------LBH-------------------\n");
	for (int i = 0; i < points->size; i++) {
		printf("%s %.20lf %.20lf %.4lf\n",
			points->data[i].name,
			points->data[i].l,
			points->data[i].b,
			points->data[i].h);
	}
	printf("-------------------ENU-------------------\n");
	for (int i = 0; i < points->size; i++) {
		printf("%s %.4lf %.4lf %.4lf\n",
			points->data[i].name,
			points->data[i].e,
			points->data[i].n,
			points->data[i].u);
	}
}

int readPointsFile(char* pointsFileName, PointData* points) {
	FILE* fp = fopen(pointsFileName, "r");
	if (!fp) {
		printf("File opne failure\n");
		return 1;
	}

	char buffer[256] = { 0 };
	char name[NAME_SIZE] = { 0 };
	int size = 0;
	double x, y, z;
	x = 0.0;
	y = 0.0;
	z = 0.0;

	fgets(buffer, MAX_COL, fp);
	if (sscanf(buffer, "%d", &size) != 1) {
		size = 0;
	}
	
	if (size >= points->capacity) {
		int newCapacity = size + 1;
		Point* newData = (Point*)realloc(points->data, sizeof(Point) * newCapacity);
		if (!newData) {
			printf("À©ÈÝÊ§°Ü\n");
			return 2;
		}
		points->capacity = newCapacity;
		points->data = newData;
	}

	while (fgets(buffer, MAX_COL, fp)) {
		if (sscanf(buffer, "%s %lf %lf %lf",
			name, &x, &y, &z) != 4) {
			strcpy(name, " ");
			x = 0.0;
			y = 0.0;
			z = 0.0;
		} else {
			strcpy(points->data[points->size].name, name);
			points->data[points->size].x = x;
			points->data[points->size].y = y;
			points->data[points->size].z = z;
			points->data[points->size].e = 0.0;
			points->data[points->size].n = 0.0;
			points->data[points->size].u = 0.0;
			points->data[points->size].l = 0.0;
			points->data[points->size].b = 0.0;
			points->data[points->size].h = 0.0;
			points->size++;
		}
	}
	fclose(fp);
	return 0;
}