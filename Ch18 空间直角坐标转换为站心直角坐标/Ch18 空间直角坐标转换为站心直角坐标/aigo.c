#include "ch18.h"

#define A  6378137.0 // 长半轴
#define F  1.0 / 298.257223563 // 扁率
#define B  -(A * F - A) // 短半轴
#define E  sqrt(A * A - B * B) / A // 第一偏心率
#define E_PRIME sqrt(A * A - B * B) / B // 第二偏心率


void xyz2lbh(double* xyz, double* lbh) {
	double theta = atan((xyz[2] * A) / (sqrt(xyz[0] * xyz[0] + xyz[1] * xyz[1]) * B));

	lbh[0] = atan(xyz[1] / xyz[0]);
	lbh[0] += PI; // 让其范围在 (-PI, PI);
	lbh[1] = atan((xyz[2] + pow(E_PRIME, 2) * B * pow(sin(theta), 3)) /
		(sqrt(xyz[0] * xyz[0] + xyz[1] * xyz[1]) - pow(E, 2) * A * pow(cos(theta), 3)));

	double N = A / sqrt(1 - pow(E, 2) * pow(sin(lbh[1]), 2));

	lbh[2] = (sqrt(xyz[0] * xyz[0] + xyz[1] * xyz[1])) / (cos(lbh[1])) - N;
}

void getPointDataLBH(PointData* points) {
	double xyz[3] = { 0 };
	double lbh[3] = { 0 };

	for (int i = 0; i < points->size; i++) {
		xyz[0] = points->data[i].x;
		xyz[1] = points->data[i].y;
		xyz[2] = points->data[i].z;

		xyz2lbh(xyz, lbh);

		points->data[i].l = lbh[0];
		points->data[i].b = lbh[1];
		points->data[i].h = lbh[2];
	}
}

Matrix* getTMat(double l, double b) { // 获取旋转矩阵
	Matrix* t = creatMat(3, 3);
	t->mat[0][0] = -sin(b) * cos(l);
	t->mat[0][1] = -sin(b) * sin(l);
	t->mat[0][2] = cos(b);
	t->mat[1][0] = -sin(l);
	t->mat[1][1] = cos(l);
	t->mat[1][2] = 0;
	t->mat[2][0] = cos(b) * cos(l);
	t->mat[2][1] = cos(b) * sin(l);
	t->mat[2][2] = sin(b);
	return t;
}

void xyz2enu(Point center, Point* toConver) {
	Matrix* center_xyz = creatMat(3, 1);
	center_xyz->mat[0][0] = center.x;
	center_xyz->mat[1][0] = center.y;
	center_xyz->mat[2][0] = center.z;
	Matrix* toConver_xyz = creatMat(3, 1);
	toConver_xyz->mat[0][0] = toConver->x;
	toConver_xyz->mat[1][0] = toConver->y;
	toConver_xyz->mat[2][0] = toConver->z;

	Matrix* toConverSubCenter = subMat(toConver_xyz, center_xyz);
	Matrix* t = getTMat(center.l, center.b);
	Matrix* res = mulMat(t, toConverSubCenter);
	toConver->e = res->mat[0][0];
	toConver->n = res->mat[1][0];
	toConver->u = res->mat[2][0];
	freeMat(center_xyz);
	freeMat(toConver_xyz);
	freeMat(toConverSubCenter);
	freeMat(t);
	freeMat(res);
}

void getPointDataENU(Point center, PointData* points) {
	for (int i = 0; i < points->size; i++) {
		xyz2enu(center, &points->data[i]);
	}
}