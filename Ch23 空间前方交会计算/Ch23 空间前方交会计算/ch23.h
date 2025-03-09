#pragma once

#include <iostream>
#include <math.h>

#define FILENAME "../data/bhl1.txt"
#define PI 3.14159265358

/*
* 外方位元素
*/
class OOE {
public:
	double X_s; // 模型基线分量
	double Y_s;
	double Z_s;
	double phi; // 偏角
	double omega; // 倾角
	double kappa; // 旋角

	void print();
};

/*
* 内方位元素
*/
class IOE {
public:
	double x;
	double y;
	double f;

	void print();
};

/*
* 空间辅助坐标
*/
class SAC {
public:
	double u;
	double v;
	double w;

	void calcaulate(IOE ioe, OOE ooe);

	void print();
};

/*
* 投影系数
*/
class ProjectionFactor {
public:
	double N_1;
	double N_2;

	void calculate(OOE ooe1, OOE ooe2, SAC sac1, SAC sac2);

	void print();
};

/*
* 地面坐标
*/
class GroundCoord {
public:
	double X;
	double Y;
	double Z;

	void calculate(OOE ooe1, OOE ooe2, SAC sac1, SAC sac2, ProjectionFactor pf);

	void print();
};
bool initData(IOE& ioe1, OOE& ooe1, IOE& ioe2, OOE& ooe2);