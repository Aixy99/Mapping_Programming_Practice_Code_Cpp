#pragma once

#include <iostream>
#include <string>
#include <cmath>

using DMS = struct DMS{
	int d; // 度
	int m; // 分
	int s; // 秒
};

using LB = struct LB {
	DMS L; // 经度
	DMS B; // 纬度
};

/*
* 图幅编号
*/
class PictureNum {
public:

	/*
	* 比例尺
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
	LB lb, addLB; // 经纬度，经纬度增量
	Scale scale; // 图幅比例尺

	int _1_m_row, _1_m_col, _500_k, _250_k, _100_k, _50_k, _25_k, _10_k;
	std::string pictureNumStr; // 图幅编号（字符串）
	LB downLeft, downRight, upLeft, upRight; // 轮廓点

	LB* diff; // 经纬差

private:

	std::string getScaleStr();

	/*******************计算图幅编号*******************/

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

	/*******************计算轮廓点经纬度*******************/

	void calOtherContourLB(LB _leftDown, Scale s); // 计算其他三点的轮廓坐标

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
