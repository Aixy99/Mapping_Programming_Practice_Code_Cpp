#include "ch15.h"

void printPoints(PointArray* points) {
	for (int i = 0; i < points->size; i++) {
		printf("%s\t%lf\t%lf\n",
			points->data[i].name,
			points->data[i].x,
			points->data[i].y);
	}
}

int main() {
	char* pointDataFileName = "../data/coord.txt";

	PointArray* points = creatPointArray(1);
	readPointDataFile(pointDataFileName, points);
	Triangle* tris = (Triangle*)malloc(sizeof(Triangle) * 6);

	tris[0] = creatTriangle("A", "B", "H", points);
	tris[1] = creatTriangle("B", "H", "C", points);
	tris[2] = creatTriangle("H", "G", "C", points);
	tris[3] = creatTriangle("C", "G", "D", points);
	tris[4] = creatTriangle("G", "D", "F", points);
	tris[5] = creatTriangle("D", "F", "E", points);

	double sumArea = 0.0;
	printf("序号\t边1\t边2\t边3\t面积\n");
	for (int i = 0; i < 6; i++) {
		printf("%-d\t%.3lf\t%.3lf\t%.3lf\t%.3lf\n",
			i + 1,
			tris[i].sideA,
			tris[i].sideB,
			tris[i].sideC,
			tris[i].area);
		sumArea += tris[i].area;
	}

	printf("\n\n总地块面积：%.3lf\n", sumArea);

	free(tris);
	freePointArray(points);
	return 0;
}