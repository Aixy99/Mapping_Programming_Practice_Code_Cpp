#include "ch24.h"

int get_int_num() {
	int num;
	while(!(std::cin >> num)) {
		std::cout << "输入非纯数字，重新输入：";
		std::cin.clear();
		std::cin.ignore(LLONG_MAX, '\n');
	}
	return num;
}

double get_double_num() {
	double num;
	while(!(std::cin >> num)) {
		std::cout << "输入非纯数字，重新输入：";
		std::cin.clear();
		std::cin.ignore(LLONG_MAX, '\n');
	}
	return num;
}

int select_mode() {
	std::cout << "1. 经纬度计算图幅编号" << std::endl;
	std::cout << "2. 图幅编号计算图廓经纬度" << std::endl;
	std::cout << "* 选择计算模式（1-2）：";

	int select;
	while(1) {
		select = get_int_num();
		if(select != 1 && select != 2) {
			std::cout << "输入错误，请重新输入（1-2）：";
			continue;
		}
		break;
	}
	return select;
}

void show_title() {
	system("cls");
	std::cout << "+------------------------------------------------------+" << std::endl;
	std::cout << "|-------------------图幅信息计算工具-------------------|" << std::endl;
	std::cout << "+------------------------------------------------------+" << std::endl;
}

LB get_lb() {
	double l, b;
	std::cout << "输入经度（DD.MMSS）：";
	l = get_double_num();
	std::cout << "输入纬度（DD.MMSS）：";
	b = get_double_num();
	LB lb = setLB(l, b);
	return lb;
}

PictureNum::Scale select_scale() {
	std::cout << "------------------------------" << std::endl;
	std::cout << "1. 1:100万" << std::endl;
	std::cout << "2. 1:50万" << std::endl;
	std::cout << "3. 1:25万" << std::endl;
	std::cout << "4. 1:10万" << std::endl;
	std::cout << "5. 1:5万" << std::endl;
	std::cout << "6. 1:2.5万" << std::endl;
	std::cout << "7. 1:1万" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "* 选择计算比例尺（1-7）：" << std::endl;

	int select;
	while(1) {
		select = get_int_num();
		if(select < 1 && select > 7) {
			std::cout << "输入错误，请重新输入（1-7）：";
			continue;
		}
		break;
	}
	return (PictureNum::Scale)(select - 1);
}

int select_old_or_new_pn() {
	std::cout << "------------------------------" << std::endl;
	std::cout << "1. 旧图幅编号" << std::endl;
	std::cout << "2. 新图幅编号" << std::endl;
	std::cout << "* 选择图幅编号类型（1-2）：" << std::endl;

	int select;
	while(1) {
		select = get_int_num();
		if(select != 1 && select != 2) {
			std::cout << "输入错误，请重新输入（1-2）：";
			continue;
		}
		break;
	}
	return select - 1;
}

void by_lb_cal_pn() {
	LB lb = get_lb();
	PictureNum pn(lb);
	pn.setScale(select_scale());
	int new_or_old = select_old_or_new_pn();
	show_title();
	pn.print(new_or_old);
}

void by_pn_cal_lb() {
	int new_or_old = select_old_or_new_pn();
	PictureNum::Scale scale = select_scale();
	std::cout << "------------------------------" << std::endl;
	std::string pn_str;
	std::cout << "输入图幅编号字符串：";
	std::cin >> pn_str;

	PictureNum pn(0, 0);
	if(!pn.byPNcalLB(pn_str, new_or_old, scale)) {
		std::cout << "输入格式有误，解析失败！" << std::endl;
		return;
	}
	pn.setScale(scale);
	show_title();
	pn.print(new_or_old);
}

/**
 * @brief 写的狗屎图幅编号计算
 * @return 
 */
int main() {
	while(1) {
		show_title();
		switch(select_mode()) {
		case 1:
			by_lb_cal_pn();
			break;
		case 2:
			by_pn_cal_lb();
			break;
		}
		system("pause");
	}
	return 0;
}