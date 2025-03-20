#pragma once

#include <iostream>
#include <string>
#include <cmath>

using DMS = struct DMS{
	int d; // ��
	int m; // ��
	int s; // ��
};

using LB = struct LB {
	DMS L; // ����
	DMS B; // γ��
};

/*
* ͼ�����
*/
class PictureNum {
public:

	/*
	* ������
	*/
	enum class Scale : int {
		_1_M = 0,
		_500_K,
		_250_K,
		_100_K,
		_50_K,
		_25_K,
		_10_K,
		MAX
	};

	PictureNum(double l, double b);

	PictureNum(LB _lb);

	~PictureNum();

	void setScale(Scale s);

	void calRowCol(int& row, int& col);

	void print(int select);

	bool byPNcalLB(const std::string pn_str, int new_or_old, PictureNum::Scale s);

	bool decodeNewPN(std::string str);

private:
	LB lb, addLB; // ��γ�ȣ���γ������
	Scale scale; // ͼ��������

	int _1_m_row, _1_m_col, _500_k, _250_k, _100_k, _50_k, _25_k, _10_k;
	std::string pictureNumStr; // ͼ����ţ��ַ�����
	LB downLeft, downRight, upLeft, upRight; // ������

	LB* diff; // ��γ��

private:

	std::string getScaleStr();

	/*******************����ͼ�����*******************/

	void cal_1M_Num();

	void cal_500K_Num();

	void cal_250K_Num();

	void cal_100K_Num();

	void cal_50K_Num();
	
	void cal_25K_Num();

	void cal_10K_Num();

	void calOldNum();

	void calNewNum();

	void calNum(int new_or_old);

	/*******************���������㾭γ��*******************/

	void calOtherContourLB(LB _leftDown, Scale s); // ���������������������

	LB calContourLB(Scale s);
};

DMS setDMS(double dms);
LB setLB(DMS l, DMS b);
LB setLB(double l, double b);

std::ostream& operator<<(std::ostream& cout, DMS& dms);
std::ostream& operator<<(std::ostream& cout, LB& bl);
int operator/(DMS d1, DMS d2);
DMS operator/(DMS d1, int num);
DMS operator-(DMS d1, DMS d2);
DMS operator+(DMS d1, DMS d2);
DMS operator*(DMS d1, int num);
