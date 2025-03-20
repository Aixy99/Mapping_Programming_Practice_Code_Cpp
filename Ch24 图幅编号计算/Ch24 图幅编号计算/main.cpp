#include "ch24.h"

int get_int_num() {
	int num;
	while(!(std::cin >> num)) {
		std::cout << "����Ǵ����֣��������룺";
		std::cin.clear();
		std::cin.ignore(LLONG_MAX, '\n');
	}
	return num;
}

double get_double_num() {
	double num;
	while(!(std::cin >> num)) {
		std::cout << "����Ǵ����֣��������룺";
		std::cin.clear();
		std::cin.ignore(LLONG_MAX, '\n');
	}
	return num;
}

int select_mode() {
	std::cout << "1. ��γ�ȼ���ͼ�����" << std::endl;
	std::cout << "2. ͼ����ż���ͼ����γ��" << std::endl;
	std::cout << "* ѡ�����ģʽ��1-2����";

	int select;
	while(1) {
		select = get_int_num();
		if(select != 1 && select != 2) {
			std::cout << "����������������루1-2����";
			continue;
		}
		break;
	}
	return select;
}

void show_title() {
	system("cls");
	std::cout << "+------------------------------------------------------+" << std::endl;
	std::cout << "|-------------------ͼ����Ϣ���㹤��-------------------|" << std::endl;
	std::cout << "+------------------------------------------------------+" << std::endl;
}

LB get_lb() {
	double l, b;
	std::cout << "���뾭�ȣ�DD.MMSS����";
	l = get_double_num();
	std::cout << "����γ�ȣ�DD.MMSS����";
	b = get_double_num();
	LB lb = setLB(l, b);
	return lb;
}

PictureNum::Scale select_scale() {
	std::cout << "------------------------------" << std::endl;
	std::cout << "1. 1:100��" << std::endl;
	std::cout << "2. 1:50��" << std::endl;
	std::cout << "3. 1:25��" << std::endl;
	std::cout << "4. 1:10��" << std::endl;
	std::cout << "5. 1:5��" << std::endl;
	std::cout << "6. 1:2.5��" << std::endl;
	std::cout << "7. 1:1��" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "* ѡ���������ߣ�1-7����" << std::endl;

	int select;
	while(1) {
		select = get_int_num();
		if(select < 1 && select > 7) {
			std::cout << "����������������루1-7����";
			continue;
		}
		break;
	}
	return (PictureNum::Scale)(select - 1);
}

int select_old_or_new_pn() {
	std::cout << "------------------------------" << std::endl;
	std::cout << "1. ��ͼ�����" << std::endl;
	std::cout << "2. ��ͼ�����" << std::endl;
	std::cout << "* ѡ��ͼ��������ͣ�1-2����" << std::endl;

	int select;
	while(1) {
		select = get_int_num();
		if(select != 1 && select != 2) {
			std::cout << "����������������루1-2����";
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
	std::cout << "����ͼ������ַ�����";
	std::cin >> pn_str;

	PictureNum pn(0, 0);
	if(!pn.byPNcalLB(pn_str, new_or_old, scale)) {
		std::cout << "�����ʽ���󣬽���ʧ�ܣ�" << std::endl;
		return;
	}
	pn.setScale(scale);
	show_title();
	pn.print(new_or_old);
}

/**
 * @brief д�Ĺ�ʺͼ����ż���
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