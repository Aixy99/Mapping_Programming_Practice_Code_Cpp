#include "ch15.h"

double getTwoPointDistance(Point p1, Point p2) {
	double dis = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	return dis;
}

void initPoint(Point p) {
	memcpy(p.name, " ", 2);
	p.x = 0.0;
	p.y = 0.0;
}

void initTriangle(Triangle t) {
	initPoint(t.a);
	initPoint(t.b);
	initPoint(t.c);
	t.sideA = 0.0;
	t.sideB = 0.0;
	t.sideC = 0.0;
	t.area = 0.0;
}

Triangle creatTriangle(char* a, char* b, char* c, PointArray* points) {
	Triangle t;
	initTriangle(t);

	if (!strcmp(a, b) || !strcmp(a, c) || !strcmp(b, c)) {
		printf("点错误：点相同\n");
		return t;
	}

	Point pa, pb, pc;
	int isHave[3] = { 0 };

	for (int i = 0; i < points->size; i++) {
		if (!strcmp(a, points->data[i].name)) {
			pa = points->data[i];
			isHave[0] = 1;
		} else if (!strcmp(b, points->data[i].name)) {
			pb = points->data[i];
			isHave[1] = 1;
		} else if (!strcmp(c, points->data[i].name)) {
			pc = points->data[i];
			isHave[2] = 1;
		}
	}
	for (int i = 0; i < 3; i++) {
		if (!isHave[i]) {
			printf("点错误： 未找到点\n");
			return t;
		}
	}

	double side[3] = { 0.0 };
	side[0] = getTwoPointDistance(pa, pb);
	side[1] = getTwoPointDistance(pa, pc);
	side[2] = getTwoPointDistance(pc, pb);

	double area, s;
	s = 0.0;
	area = 0.0;

	s = (side[0] + side[1] + side[2]) / 2.0;
	area = sqrt(s * (s - side[0]) * (s - side[1]) * (s - side[2]));

	t.a = pa;
	t.b = pb;
	t.c = pc;
	t.sideA = side[0];
	t.sideB = side[1];
	t.sideC = side[2];
	t.area = area;
	return t;
}