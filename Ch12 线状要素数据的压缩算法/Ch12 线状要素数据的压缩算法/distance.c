#include "dp.h"
double culTwoPointDistance(Point p1, Point p2) {
	double distance = 0.0;
	distance = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	return distance;
}

double culPointToLineDistance(Point p0, Point pi, Point pn) {
	double distance = 0.0;
	double l0n = culTwoPointDistance(p0, pn);
	double lin = culTwoPointDistance(pi, pn);
	double l0i = culTwoPointDistance(p0, pi);
	double p = (l0i + l0n + lin) / 2;
	double s = sqrt(p * (p - l0i) * (p - lin) * (p - l0n));
	distance = 2 * s / l0n;
	return distance;
}

/*
* 计算每个点到直线的距离
*/
void culPointDistance(PointArray* pointData, Point p0, Point pn, int start, int end) {
	for (int i = 0; i < pointData->size; i++) {
		pointData->data[i].distance =
			culPointToLineDistance(p0, pointData->data[i], pn);
		if (pointData->data[i].num < start || pointData->data[i].num > end) {
			pointData->data[i].distance = 0.0;
		}
	}
}

int findMaxDistance(PointArray* pointData, int *maxDistanceNum) {
	double max = pointData->data[0].distance;
	for (int i = 0; i < pointData->size; i++) {
		if (pointData->data[i].distance > max) {
			max = pointData->data[i].distance;
			*maxDistanceNum = pointData->data[i].num;
		}
	}
	return max;
}

void initPoint(Point* p) {
	p->num = 0;
	p->x = 0.0;
	p->y = 0.0;
	p->distance = 0.0;
}

void delPoint(PointArray* pointData, int start, int end) {
	for (int i = 0; i < pointData->size; i++) {
		if (pointData->data[i].num > start && pointData->data[i].num < end) {
			initPoint(&pointData->data[i]);
		}
	}
}

void showDistance(PointArray* pointData) {
	for (int i = 0; i < pointData->size; i++) {
		printf("%d\t%lf\n", pointData->data[i].num, pointData->data[i].distance);
	}
}

void dp(PointArray* pointData, int start, int end) {
	printf("当前过程：%d->%d\n\n", start, end);

	Point* p0, * pn;
	for (int i = 0; i < pointData->size; i++) {
		if (pointData->data[i].num == start) {
			p0 = &pointData->data[i];
		}
		if (pointData->data[i].num == end) {
			pn = &pointData->data[i];
		}
	}
	culPointDistance(pointData, *p0, *pn, start, end);
	//showDistance(pointData);
	int maxDistancePointNUm = 0;
	double maxDistance = findMaxDistance(pointData, &maxDistancePointNUm);
	if (maxDistance < D_T) {
		delPoint(pointData, start, end);
		return;
	} else {
		dp(pointData, start, maxDistancePointNUm);
		dp(pointData, maxDistancePointNUm, end);
	}
}