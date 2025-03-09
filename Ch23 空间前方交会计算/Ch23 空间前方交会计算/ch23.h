#pragma once

#include <iostream>
#include <math.h>

#define FILENAME "../data/bhl1.txt"
#define PI 3.14159265358

/*
* �ⷽλԪ��
*/
class OOE {
public:
	double X_s; // ģ�ͻ��߷���
	double Y_s;
	double Z_s;
	double phi; // ƫ��
	double omega; // ���
	double kappa; // ����

	void print();
};

/*
* �ڷ�λԪ��
*/
class IOE {
public:
	double x;
	double y;
	double f;

	void print();
};

/*
* �ռ丨������
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
* ͶӰϵ��
*/
class ProjectionFactor {
public:
	double N_1;
	double N_2;

	void calculate(OOE ooe1, OOE ooe2, SAC sac1, SAC sac2);

	void print();
};

/*
* ��������
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