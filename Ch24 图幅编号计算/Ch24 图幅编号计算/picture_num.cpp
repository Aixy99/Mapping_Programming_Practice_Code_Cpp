#include "ch24.h"

std::ostream& operator<<(std::ostream& cout, DMS& dms) {
	if(dms.m < 0 || dms.s < 0) {
		if(dms.d == 0) {
			cout << "-"
				<< dms.d << "."
				<< (dms.m == 0 ? "0" : dms.m > -10 ? "0" : "")
				<< (dms.m < 0 ? -dms.m : dms.m)
				<< (dms.s == 0 ? "0" : dms.s > -10 ? "0" : "")
				<< (dms.s < 0 ? -dms.s : dms.s);
		} else {
			cout << dms.d << "."
				<< (dms.m == 0 ? "0" : dms.m > -10 ? "0" : "")
				<< (dms.m < 0 ? -dms.m : dms.m)
				<< (dms.s == 0 ? "0" : dms.s > -10 ? "0" : "")
				<< (dms.s < 0 ? -dms.s : dms.s);
		}
	} else {
		cout << dms.d << '.'
			<< (dms.m < 10 ? "0" : "")
			<< dms.m
			<< (dms.s < 10 ? "0" : "")
			<< dms.s;
	}
	return cout;
}

std::ostream& operator<<(std::ostream& cout, LB& bl) {
	cout << '(' << bl.L << ',' << bl.B << ')';
	return cout;
}

int operator/(DMS d1, DMS d2) {
	int res;
	int a = d1.s + d1.m * 60 + d1.d * 3600;
	int b = d2.s + d2.m * 60 + d2.d * 3600;

	res = a / b;
	return res;
}

DMS operator/(DMS d1, int num) {
	DMS res;
	int d1s = d1.d * 3600 + d1.m * 60 + d1.s;
	int ress = d1s / num;

	res.d = ress / 3600;
	ress %= 3600;
	res.m = ress / 60;
	ress %= 60;
	res.s = ress;
	return res;
}

DMS operator-(DMS d1, DMS d2) {
	DMS res;
	int d1s = d1.d * 3600 + d1.m * 60 + d1.s;
	int d2s = d2.d * 3600 + d2.m * 60 + d2.s;
	int ress = d1s - d2s;

	res.d = ress / 3600;
	ress %= 3600;
	res.m = ress / 60;
	ress %= 60;
	res.s = ress;
	return res;
}

DMS operator+(DMS d1, DMS d2) {
	DMS res;
	int d1s = d1.d * 3600 + d1.m * 60 + d1.s;
	int d2s = d2.d * 3600 + d2.m * 60 + d2.s;
	int ress = d1s + d2s;

	res.d = ress / 3600;
	ress %= 3600;
	res.m = ress / 60;
	ress %= 60;
	res.s = ress;
	return res;
}

DMS operator*(DMS d1, int num) {
	DMS res;
	int d1s = d1.d * 3600 + d1.m * 60 + d1.s;
	int ress = d1s * num;

	res.d = ress / 3600;
	ress %= 3600;
	res.m = ress / 60;
	ress %= 60;
	res.s = ress;
	return res;
}

DMS setDMS(double dms) {
	DMS res;
	res.d = floor(dms);
	res.m = floor(dms * 100) - res.d * 100;
	res.s = floor(dms * 10000) - res.d * 10000 - res.m * 100;

	while(res.s >= 60) {
		res.m++;
		res.s -= 60;
	}
	while(res.m >= 60) {
		res.d++;
		res.m -= 60;
	}
	return res;
}

LB setLB(DMS l, DMS b) {
	LB res;
	res.B = b;
	res.L = l;
	return res;
}

LB setLB(double l, double b) {
	LB res;
	res.B = setDMS(b);
	res.L = setDMS(l);
	return res;
}

PictureNum::PictureNum(double l, double b) : scale(Scale::_1_M), pictureNumStr("") {
	this->lb = setLB(l, b);

	this->addLB = setLB(0, 0);

	this->downLeft = setLB(0, 0);
	this->downLeft = setLB(0, 0);
	this->downRight = setLB(0, 0);
	this->downRight = setLB(0, 0);
	this->upLeft = setLB(0, 0);
	this->upLeft = setLB(0, 0);
	this->upRight = setLB(0, 0);
	this->upRight = setLB(0, 0);

	this->_1_m_row = 0;
	this->_1_m_col = 0;
	this->_500_k = 0;
	this->_250_k = 0;
	this->_100_k = 0;
	this->_50_k = 0;
	this->_25_k = 0;
	this->_10_k = 0;

	this->diff = new LB[(int)Scale::MAX];
	this->diff[0] = setLB(6.0000, 4.0000);
	this->diff[1] = setLB(3.0000, 2.0000);
	this->diff[2] = setLB(1.3000, 1.0000);
	this->diff[3] = setLB(0.3000, 0.2000);
	this->diff[4] = setLB(0.1500, 0.1000);
	this->diff[5] = setLB(0.0730, 0.0500);
	this->diff[6] = setLB(0.0345, 0.0230);

	this->cal_1M_Num();
	this->cal_500K_Num();
	this->cal_250K_Num();
	this->cal_100K_Num();
	this->cal_50K_Num();
	this->cal_25K_Num();
	this->cal_10K_Num();

	this->pictureNumStr = "";
}

PictureNum::PictureNum(LB _lb) {
	this->lb = _lb;

	this->addLB = setLB(0, 0);

	this->downLeft = setLB(0, 0);
	this->downLeft = setLB(0, 0);
	this->downRight = setLB(0, 0);
	this->downRight = setLB(0, 0);
	this->upLeft = setLB(0, 0);
	this->upLeft = setLB(0, 0);
	this->upRight = setLB(0, 0);
	this->upRight = setLB(0, 0);

	this->_1_m_row = 0;
	this->_1_m_col = 0;
	this->_500_k = 0;
	this->_250_k = 0;
	this->_100_k = 0;
	this->_50_k = 0;
	this->_25_k = 0;
	this->_10_k = 0;

	this->diff = new LB[(int)Scale::MAX];
	this->diff[0] = setLB(6.0000, 4.0000);
	this->diff[1] = setLB(3.0000, 2.0000);
	this->diff[2] = setLB(1.3000, 1.0000);
	this->diff[3] = setLB(0.3000, 0.2000);
	this->diff[4] = setLB(0.1500, 0.1000);
	this->diff[5] = setLB(0.0730, 0.0500);
	this->diff[6] = setLB(0.0345, 0.0230);

	this->cal_1M_Num();
	this->cal_500K_Num();
	this->cal_250K_Num();
	this->cal_100K_Num();
	this->cal_50K_Num();
	this->cal_25K_Num();
	this->cal_10K_Num();

	this->calOldNum();
}

PictureNum::~PictureNum() {
	if(this->diff != nullptr) {
		delete[] this->diff;
		this->diff = nullptr;
	}
}

void PictureNum::setScale(Scale s) {
	this->scale = s;
}

std::string PictureNum::getScaleStr() {
	std::string strScale = "";
	switch(this->scale) {
	case Scale::_1_M:
		strScale = "1:100万";
		break;
	case Scale::_500_K:
		strScale = "1:50万";
		break;
	case Scale::_250_K:
		strScale = "1:25万";
		break;
	case Scale::_100_K:
		strScale = "1:10万";
		break;
	case Scale::_50_K:
		strScale = "1:5万";
		break;
	case Scale::_25_K:
		strScale = "1:2.5万";
		break;
	case Scale::_10_K:
		strScale = "1:1万";
		break;
	}

	return strScale;
}

void PictureNum::cal_1M_Num() {
	this->_1_m_row = this->lb.B.d / 4 + 1;
	this->_1_m_col = this->lb.L.d / 6 + 31;
}

void PictureNum::cal_500K_Num() {
	this->addLB.B = this->lb.B;
	this->addLB.B.d -= this->lb.B.d / 4 * 4;
	this->addLB.L = this->lb.L;
	this->addLB.L.d -= this->lb.L.d / 6 * 6;

	this->_500_k = (this->addLB.L / diff[(int)Scale::_500_K].L + 1)
		+ (1 - this->addLB.B / diff[(int)Scale::_500_K].B) * 2;
}

void PictureNum::cal_250K_Num() {
	this->_250_k = (this->addLB.L / diff[(int)Scale::_250_K].L + 1)
		+ (3 - this->addLB.B / diff[(int)Scale::_250_K].B) * 4;
}

void PictureNum::cal_100K_Num() {
	this->_100_k = (this->addLB.L / diff[(int)Scale::_100_K].L + 1)
		+ (11 - this->addLB.B / diff[(int)Scale::_100_K].B) * 12;
}

void PictureNum::cal_50K_Num() {
	LB _leftDown = calContourLB(Scale::_100_K);
	//相对于_100_k的经纬度增量
	LB _100_k_addLB = { lb.L - _leftDown.L, lb.B - _leftDown.B };
	this->_50_k = (_100_k_addLB.L / diff[(int)Scale::_50_K].L + 1)
		+ (1 - _100_k_addLB.B / diff[(int)Scale::_50_K].B) * 2;
}

void PictureNum::cal_25K_Num() {
	LB _leftDown = calContourLB(Scale::_50_K);
	//相对于_50_k的经纬度增量
	LB _50_k_addLB = { lb.L - _leftDown.L, lb.B - _leftDown.B };
	this->_25_k = (_50_k_addLB.L / diff[(int)Scale::_25_K].L + 1)
		+ (1 - _50_k_addLB.B / diff[(int)Scale::_25_K].B) * 2;
}

void PictureNum::cal_10K_Num() {
	LB _leftDown = calContourLB(Scale::_100_K);
	//相对于_100_k的经纬度增量
	LB _100_k_addLB = { lb.L - _leftDown.L, lb.B - _leftDown.B };

	this->_10_k = (_100_k_addLB.L / diff[(int)Scale::_10_K].L + 1)
		+ (7 - _100_k_addLB.B / diff[(int)Scale::_10_K].B) * 8;
}

void PictureNum::calOldNum() {
	switch(this->scale) {
	case Scale::_1_M:
		this->pictureNumStr = (char)('A' - 1 + this->_1_m_row) + std::to_string(this->_1_m_col);
		break;
	case Scale::_500_K:
		this->pictureNumStr = (char)('A' - 1 + this->_1_m_row) + std::to_string(this->_1_m_col)
			+ std::to_string(this->_500_k);
		break;
	case Scale::_250_K:
		this->pictureNumStr = (char)('A' - 1 + this->_1_m_row) + std::to_string(this->_1_m_col)
			+ (this->_250_k < 10 ? "0" : "") + std::to_string(this->_250_k);
		break;
	case Scale::_100_K:
		this->pictureNumStr = (char)('A' - 1 + this->_1_m_row) + std::to_string(this->_1_m_col)
			+ (this->_100_k < 100 ? this->_100_k < 10 ? "00" : "0" : "")
			+ std::to_string(this->_100_k);
		break;
	case Scale::_50_K:
		this->pictureNumStr = (char)('A' - 1 + this->_1_m_row) + std::to_string(this->_1_m_col)
			+ (this->_100_k < 100 ? this->_100_k < 10 ? "00" : "0" : "")
			+ std::to_string(this->_100_k)
			+ (char)('A' - 1 + this->_50_k);
		break;
	case Scale::_25_K:
		this->pictureNumStr = (char)('A' - 1 + this->_1_m_row) + std::to_string(this->_1_m_col)
			+ (this->_100_k < 100 ? this->_100_k < 10 ? "00" : "0" : "")
			+ std::to_string(this->_100_k)
			+ (char)('A' - 1 + this->_50_k) + std::to_string(this->_25_k);
		break;
	case Scale::_10_K:
		this->pictureNumStr = (char)('A' - 1 + this->_1_m_row) + std::to_string(this->_1_m_col)
			+ (this->_100_k < 100 ? this->_100_k < 10 ? "00" : "0" : "")
			+ std::to_string(this->_100_k)
			+ (this->_10_k < 10 ? "0" : "")
			+ std::to_string(this->_10_k);
		break;
	}
}

void PictureNum::calRowCol(int& row, int& col) {
	int newRow, newCol;
	switch(this->scale) {
	case PictureNum::Scale::_1_M:
		row = -1;
		col = -1;
		break;
	case PictureNum::Scale::_500_K:
		row = this->_500_k % 2 ? this->_500_k / 2 + 1 : this->_500_k / 2;
		col = this->_500_k % 2 ? this->_500_k % 2 : 2;
		break;
	case PictureNum::Scale::_250_K:
		row = this->_250_k % 4 ? this->_250_k / 4 + 1 : this->_250_k / 4;
		col = this->_250_k % 4 ? this->_250_k % 4 : 4;
		break;
	case PictureNum::Scale::_100_K:
		row = this->_100_k % 12 ? this->_100_k / 12 + 1 : this->_100_k / 12;
		col = this->_100_k % 12 ? this->_100_k % 12 : 12;
		break;
	case PictureNum::Scale::_50_K:
		// 先计算1:100k
		row = this->_100_k % 12 ? this->_100_k / 12 + 1 : this->_100_k / 12;
		col = this->_100_k % 12 ? this->_100_k % 12 : 12;

		// 1:50k
		row = row * 2 - 1;
		col = col * 2 - 1;

		newRow = (this->_50_k % 2 ? this->_50_k / 2 + 1 : this->_50_k / 2);
		newCol = this->_50_k % 2 ? this->_50_k % 2 : 2;

		row += newRow - 1;
		col += newCol - 1;
		break;
	case PictureNum::Scale::_25_K:
		// 先计算1:100k
		row = this->_100_k % 12 ? this->_100_k / 12 + 1 : this->_100_k / 12;
		col = this->_100_k % 12 ? this->_100_k % 12 : 12;

		// 1:50k
		row = row * 2 - 1;
		col = col * 2 - 1;

		newRow = (this->_50_k % 2 ? this->_50_k / 2 + 1 : this->_50_k / 2);
		newCol = this->_50_k % 2 ? this->_50_k % 2 : 2;

		row += newRow - 1;
		col += newCol - 1;

		// 1:25k
		row = row * 2 - 1;
		col = col * 2 - 1;

		newRow = this->_25_k % 2 ? this->_25_k / 2 + 1 : this->_25_k / 2;
		newCol = this->_25_k % 2 ? this->_25_k % 2 : 2;

		row += newRow - 1;
		col += newCol - 1;
		break;
	case PictureNum::Scale::_10_K:
		// 先计算1:100k
		row = this->_100_k % 12 ? this->_100_k / 12 + 1 : this->_100_k / 12;
		col = this->_100_k % 12 ? this->_100_k % 12 : 12;

		// 1:10k
		row = row * 8 - 7;
		col = col * 8 - 7;

		newRow = this->_10_k % 8 ? this->_10_k / 8 + 1 : this->_10_k / 8;
		newCol = this->_10_k % 8 ? this->_10_k % 8 : 8;

		row += newRow - 1;
		col += newCol - 1;
		break;
	}
}

void PictureNum::calNewNum() {
	int row = 0, col = 0;
	this->calRowCol(row, col);
	switch(this->scale) {
	case Scale::_1_M:
		this->pictureNumStr = (char)('A' - 1 + this->_1_m_row) + std::to_string(this->_1_m_col);
		break;
	case Scale::_500_K:
		this->pictureNumStr = (char)('A' - 1 + this->_1_m_row) + std::to_string(this->_1_m_col)
			+ 'B'
			+ (row < 100 ? row < 10 ? "00" : "0" : "") + std::to_string(row)
			+ (col < 100 ? col < 10 ? "00" : "0" : "") + std::to_string(col);
		break;
	case Scale::_250_K:
		this->pictureNumStr = (char)('A' - 1 + this->_1_m_row) + std::to_string(this->_1_m_col)
			+ 'C'
			+ (row < 100 ? row < 10 ? "00" : "0" : "") + std::to_string(row)
			+ (col < 100 ? col < 10 ? "00" : "0" : "") + std::to_string(col);
		break;
	case Scale::_100_K:
		this->pictureNumStr = (char)('A' - 1 + this->_1_m_row) + std::to_string(this->_1_m_col)
			+ 'D'
			+ (row < 100 ? row < 10 ? "00" : "0" : "") + std::to_string(row)
			+ (col < 100 ? col < 10 ? "00" : "0" : "") + std::to_string(col);
		break;
	case Scale::_50_K:
		this->pictureNumStr = (char)('A' - 1 + this->_1_m_row) + std::to_string(this->_1_m_col)
			+ 'E'
			+ (row < 100 ? row < 10 ? "00" : "0" : "") + std::to_string(row)
			+ (col < 100 ? col < 10 ? "00" : "0" : "") + std::to_string(col);
		break;
	case Scale::_25_K:
		this->pictureNumStr = (char)('A' - 1 + this->_1_m_row) + std::to_string(this->_1_m_col)
			+ 'F'
			+ (row < 100 ? row < 10 ? "00" : "0" : "") + std::to_string(row)
			+ (col < 100 ? col < 10 ? "00" : "0" : "") + std::to_string(col);
		break;
	case Scale::_10_K:
		this->pictureNumStr = (char)('A' - 1 + this->_1_m_row) + std::to_string(this->_1_m_col)
			+ 'G'
			+ (row < 100 ? row < 10 ? "00" : "0" : "") + std::to_string(row)
			+ (col < 100 ? col < 10 ? "00" : "0" : "") + std::to_string(col);
		break;
	}
}

void PictureNum::calNum(int new_or_old) {
	this->cal_1M_Num();
	this->cal_500K_Num();
	this->cal_250K_Num();
	this->cal_100K_Num();
	this->cal_50K_Num();
	this->cal_25K_Num();
	this->cal_10K_Num();
	if(new_or_old) {
		this->calNewNum();
	} else {
		this->calOldNum();
	}
}

/**
 * @brief 计算图幅右下角
 * @param diff 经纬差
 * @param original 用来推算的原始图幅左下角坐标
 * @param size 区域大小，比如 4*4，则size = 4
 * @param num 区域号
 * @return 图幅右下角
 */
LB calLeftDown(LB diff, LB original, int size, int num) {
	LB res = setLB(0, 0);
	res.L = original.L + diff.L * (num % size ? (num % size - 1) : (size - 1));
	res.B = original.B + diff.B * (num % size ? (size - 1) - num / size : size - (num / size));
	return res;
}

void PictureNum::calOtherContourLB(LB _leftDown, Scale s) {
	this->downRight.L = downLeft.L + diff[(int)s].L;
	this->downRight.B = downLeft.B;
	this->upLeft.L = downLeft.L;
	this->upLeft.B = downLeft.B + diff[(int)s].B;
	this->upRight.L = downLeft.L + diff[(int)s].L;
	this->upRight.B = downLeft.B + diff[(int)s].B;
}

LB PictureNum::calContourLB(Scale s) {
	LB _leftDown = setLB(0, 0);
	switch(s) {
	case Scale::_1_M:
		_leftDown.L.d = (this->_1_m_col - 31) * 6;
		_leftDown.B.d = (this->_1_m_row - 1) * 4;
		break;
	case Scale::_500_K:
		_leftDown = calLeftDown(this->diff[(int)Scale::_500_K], calContourLB(Scale::_1_M), 2, this->_500_k);
		break;
	case Scale::_250_K:
		_leftDown = calLeftDown(this->diff[(int)Scale::_250_K], calContourLB(Scale::_1_M), 4, this->_250_k);
		break;
	case Scale::_100_K:
		_leftDown = calLeftDown(this->diff[(int)Scale::_100_K], calContourLB(Scale::_1_M), 12, this->_100_k);
		break;
	case Scale::_50_K:
		_leftDown = calLeftDown(this->diff[(int)Scale::_50_K], calContourLB(Scale::_100_K), 2, this->_50_k);
		break;
	case Scale::_25_K:
		_leftDown = calLeftDown(this->diff[(int)Scale::_25_K], calContourLB(Scale::_50_K), 2, this->_25_k);
		break;
	case Scale::_10_K:
		_leftDown = calLeftDown(this->diff[(int)Scale::_10_K], calContourLB(Scale::_100_K), 8, this->_10_k);
		break;
	}
	this->downLeft = _leftDown;
	calOtherContourLB(_leftDown, s);
	return _leftDown;
}

/**
 * @brief 输出图幅信息
 * @param select : 0 旧图幅，1 新图幅
 */
void PictureNum::print(int select) {
	this->calNum(select);
	std::cout << "纬度：" << this->lb.B << std::endl;
	std::cout << "经度：" << this->lb.L << std::endl;
	std::cout << "图幅编号：" << this->pictureNumStr << std::endl;
	std::cout << "比例尺：" << this->getScaleStr() << std::endl;
	std::cout << "------------图廓点经纬度(L,B)(DD.MMSS)------------" << std::endl;
	calContourLB(this->scale);
	std::cout << "左下：" << this->downLeft << std::endl;
	std::cout << "右下：" << this->downRight << std::endl;
	std::cout << "右上：" << this->upRight << std::endl;
	std::cout << "左上：" << this->upLeft << std::endl;
	std::cout << "------------接图表------------" << std::endl;

	this->lb = setLB(lb.L - diff[(int)(this->scale)].L, lb.B + diff[(int)(this->scale)].B);
	this->calNum(select);
	std::cout << this->pictureNumStr << " | ";

	this->lb = setLB(lb.L + diff[(int)(this->scale)].L, lb.B);
	this->calNum(select);
	std::cout << this->pictureNumStr << " | ";

	this->lb = setLB(lb.L + diff[(int)(this->scale)].L, lb.B);
	this->calNum(select);
	std::cout << this->pictureNumStr << "\n\n";

	this->lb = setLB(lb.L - diff[(int)(this->scale)].L * 2, lb.B - diff[(int)(this->scale)].B);
	this->calNum(select);
	std::cout << this->pictureNumStr << " | ";

	this->lb = setLB(lb.L + diff[(int)(this->scale)].L, lb.B);
	this->calNum(select);
	std::cout << this->pictureNumStr << " | ";

	this->lb = setLB(lb.L + diff[(int)(this->scale)].L, lb.B);
	this->calNum(select);
	std::cout << this->pictureNumStr << "\n\n";

	this->lb = setLB(lb.L - diff[(int)(this->scale)].L * 2, lb.B - diff[(int)(this->scale)].B);
	this->calNum(select);
	std::cout << this->pictureNumStr << " | ";

	this->lb = setLB(lb.L + diff[(int)(this->scale)].L, lb.B);
	this->calNum(select);
	std::cout << this->pictureNumStr << " | ";

	this->lb = setLB(lb.L + diff[(int)(this->scale)].L, lb.B);
	this->calNum(select);
	std::cout << this->pictureNumStr << "\n\n";
}

bool is_num(char ch) {
	if(ch >= '0' && ch <= '9') return true;
	return false;
}

bool is_num(std::string str) {
	for(int i = 0; i < str.length(); i++) {
		if(!is_num(str[i])) return false;
	}
	return true;
}

bool is_upper_letter(char ch) {
	if(ch >= 'A' && ch <= 'Z') return true;
	return false;
}

bool is_new_pn(std::string str) {
	if(str.length() != 10) return false;
	if(!is_upper_letter(str[0])) return false;
	if(!is_num(str.substr(1, 2))) return false;
	if(!is_upper_letter(str[3])) return false;
	if(!is_num(str.substr(4, 6))) return false;
	return true;
}

bool is_old_pn(std::string str, PictureNum::Scale s) {
	if(!is_upper_letter(str[0])) return false;
	switch(s) {
	case PictureNum::Scale::_1_M:
		if(str.length() != 3) return false;
		if(!is_num(str.substr(1, 2))) return false;
		break;
	case PictureNum::Scale::_500_K:
		if(str.length() != 4) return false;
		if(!is_num(str.substr(1, 3))) return false;
		break;
	case PictureNum::Scale::_250_K:
		if(str.length() != 5) return false;
		if(!is_num(str.substr(1, 4))) return false;
		break;
	case PictureNum::Scale::_100_K:
		if(str.length() != 6) return false;
		if(!is_num(str.substr(1, 5))) return false;
		break;
	case PictureNum::Scale::_50_K:
		if(str.length() != 7) return false;
		if(!is_num(str.substr(1, 6))) return false;
		break;
	case PictureNum::Scale::_25_K:
		if(str.length() != 8) return false;
		if(!is_num(str.substr(1, 7))) return false;
		break;
	case PictureNum::Scale::_10_K:
		if(str.length() != 8) return false;
		if(!is_num(str.substr(1, 7))) return false;
		break;
	}
	return true;
}

int str2num(std::string str) {
	if(!is_num(str)) return 0;
	return stoi(str);
}

bool PictureNum::decodeNewPN(std::string str) {
	Scale s;
	switch(str[3]) {
	case 'B':
		s = Scale::_500_K;
		break;
	case 'C':
		s = Scale::_250_K;
		break;
	case 'D':
		s = Scale::_100_K;
		break;
	case 'E':
		s = Scale::_50_K;
		break;
	case 'F':
		s = Scale::_25_K;
		break;
	case 'G':
		s = Scale::_10_K;
		break;
	}

	int row = str2num(str.substr(4, 3));
	int col = str2num(str.substr(7, 3));

	byPNcalLB(str.substr(0, 3), 0, Scale::_1_M);
	this->lb.L = upLeft.L + diff[(int)s].L * (col - 1);
	this->lb.B = upLeft.B - diff[(int)s].B * row;
	this->calNum(0);
	return true;
}

bool PictureNum::byPNcalLB(const std::string pn_str, int new_or_old, PictureNum::Scale s) {
	std::string temp = "";
	switch(s) {
	case Scale::_1_M:
		if(!is_old_pn(pn_str, Scale::_1_M)) return false;
		this->_1_m_row = pn_str[0] - 'A' + 1;
		this->_1_m_col = str2num(pn_str.substr(1, 2));
		break;
	case Scale::_500_K:
		if(new_or_old) {
			if(!is_new_pn(pn_str)) return false;
			if(pn_str[3] != 'B') return false;
			if(!decodeNewPN(pn_str)) return false;
		} else {
			if(!is_old_pn(pn_str, PictureNum::Scale::_500_K));
			this->_1_m_row = pn_str[0] - 'A' + 1;
			this->_1_m_col = str2num(pn_str.substr(1, 2));
			this->_500_k = pn_str[3] - '0';
		}
	case Scale::_250_K:
		if(new_or_old) {
			if(!is_new_pn(pn_str)) return false;
			if(pn_str[3] != 'C') return false;
			if(!decodeNewPN(pn_str)) return false;
		} else {
			if(!is_old_pn(pn_str, PictureNum::Scale::_250_K));
			this->_1_m_row = pn_str[0] - 'A' + 1;
			this->_1_m_col = str2num(pn_str.substr(1, 2));
			this->_250_k = str2num(pn_str.substr(3, 2));
		}
		break;
	case Scale::_100_K:
		if(new_or_old) {
			if(!is_new_pn(pn_str)) return false;
			if(pn_str[3] != 'D') return false;
			if(!decodeNewPN(pn_str)) return false;
		} else {
			if(!is_old_pn(pn_str, PictureNum::Scale::_100_K));
			this->_1_m_row = pn_str[0] - 'A' + 1;
			this->_1_m_col = str2num(pn_str.substr(1, 2));
			this->_100_k = str2num(pn_str.substr(3, 3));
		}
		break;
	case Scale::_50_K:
		if(new_or_old) {
			if(!is_new_pn(pn_str)) return false;
			if(pn_str[3] != 'E') return false;
			if(!decodeNewPN(pn_str)) return false;
		} else {
			if(!is_old_pn(pn_str, PictureNum::Scale::_50_K));
			this->_1_m_row = pn_str[0] - 'A' + 1;
			this->_1_m_col = str2num(pn_str.substr(1, 2));
			this->_100_k = str2num(pn_str.substr(3, 3));
			this->_50_k = pn_str[6] - '0';
		}
		break;
	case Scale::_25_K:
		if(new_or_old) {
			if(!is_new_pn(pn_str)) return false;
			if(pn_str[3] != 'F') return false;
			if(!decodeNewPN(pn_str)) return false;
		} else {
			if(!is_old_pn(pn_str, PictureNum::Scale::_25_K));
			this->_1_m_row = pn_str[0] - 'A' + 1;
			this->_1_m_col = str2num(pn_str.substr(1, 2));
			this->_100_k = str2num(pn_str.substr(3, 3));
			this->_50_k = pn_str[6] - '0';
			this->_50_k = pn_str[7] - '0';
		}
		break;
	case Scale::_10_K:
		if(new_or_old) {
			if(!is_new_pn(pn_str)) return false;
			if(pn_str[3] != 'G') return false;
			if(!decodeNewPN(pn_str)) return false;
		} else {
			if(!is_old_pn(pn_str, PictureNum::Scale::_10_K));
			this->_1_m_row = pn_str[0] - 'A' + 1;
			this->_1_m_col = str2num(pn_str.substr(1, 2));
			this->_100_k = str2num(pn_str.substr(3, 3));
			this->_10_k = str2num(pn_str.substr(6, 2));
		}
		break;
	}

	calContourLB(s);
	this->lb.L = this->downLeft.L + (diff[(int)s].L / 2);
	this->lb.B = this->downLeft.B + (diff[(int)s].B / 2);
	return true;
}