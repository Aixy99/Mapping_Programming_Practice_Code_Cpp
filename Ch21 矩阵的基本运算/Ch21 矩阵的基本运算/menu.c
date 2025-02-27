#include "matrix.h"
int getIntNum() {
	int num = 0;

	while(scanf("%d", &num) != 1) {
		printf("������������������\n");

		int c;
		while((c = getchar()) != '\n' && c != EOF); // ���������
	}
	return num;
}

double getDoubleNum() {
	double num = 0;

	while(scanf("%lf", &num) != 1) {
		printf("������������������\n");

		int c;
		while((c = getchar()) != '\n' && c != EOF); // ���������
	}
	return num;
}

int getRowOrCol() {
	int num = getIntNum();

	while(num < 1) {
		printf("�������0������������\n");
		num = getIntNum();
	}
	return num;
}

Matrix* getMat(int row, int col) {
	Matrix* m = creatMat(row, col);
	
	int count = 0;
	for(int i = 0; i < m->row; i++) {
		for(int j = 0; j < m->col; j++) {
			printf("������� %d ������", ++count);
			m->mat[i][j] = getDoubleNum();
		}
	}
	return m;
}

Matrix** getTwoMat() {
	int row = 0;
	int col = 0;

	printf("�������������:\n");
	row = getRowOrCol();
	printf("�������������:\n");
	col = getRowOrCol();

	Matrix** m = (Matrix**)malloc(sizeof(Matrix*) * 2);
	printf("----------���� 1----------\n");
	m[0] = getMat(row, col);
	printf("-------------------------\n");
	printf("----------���� 2----------\n");
	m[1] = getMat(row, col);
	printf("-------------------------\n");

	return m;
}

Matrix* getOneMat() {
	int row = 0;
	int col = 0;

	printf("�������������:\n");
	row = getRowOrCol();
	printf("�������������:\n");
	col = getRowOrCol();

	Matrix* m = getMat(row, col);

	return m;
}

int showMenu() {
	printf("-------------------���������-------------------\n");
	printf("                 1  �������\n");
	printf("                 2  �������\n");
	printf("                 3  �������\n");
	printf("                 4  �����������\n");
	printf("                 5  �������\n");
	printf("                 6  �����������\n");
	printf("                 7  �������\n");
	printf("                 8  ������ʽ\n");
	printf("                 9  ��������\n");
	printf("                 10 ����ת��\n");
	printf("                 0  �˳�\n");
	printf("------------------------------------------------\n");
	printf("��ѡ����Ҫ���еļ��㣨0-10��:");
	int select = getIntNum();
	while(select > 10 || select < 0) {
		printf("�������������루0-10��\n");
		select = getIntNum();
	}
	return select;
}

void calAddMat() {
	Matrix** m = getTwoMat();
	Matrix* res = addMat(m[0], m[1]);
	printMat(res);
	freeMat(&res);
	freeMat(&m[0]);
	freeMat(&m[1]);
}

void calSubMat() {
	Matrix** m = getTwoMat();
	Matrix* res = subMat(m[0], m[1]);
	printMat(res);
	freeMat(&res);
	freeMat(&m[0]);
	freeMat(&m[1]);
}

void calMulMat() {
	Matrix** m = getTwoMat();
	Matrix* res = mulMat(m[0], m[1]);
	printMat(res);
	freeMat(&res);
	freeMat(&m[0]);
	freeMat(&m[1]);
}

void calDivMat() {
	Matrix** m = getTwoMat();
	Matrix* res = divMat(m[0], m[1]);
	printMat(res);
	freeMat(&res);
	freeMat(&m[0]);
	freeMat(&m[1]);
}

void calMulMatNum() {
	Matrix* m = getOneMat();
	printf("����������\n");
	double num = getDoubleNum();
	Matrix* res = mulMatNum(m, num);
	printMat(res);
	freeMat(&res);
	freeMat(&m);
}

void calDivMatNum() {
	Matrix* m = getOneMat();
	printf("����������\n");
	double num = getDoubleNum();
	Matrix* res = divMatNum(m, num);
	printMat(res);
	freeMat(&res);
	freeMat(&m);
}

void calInvMat() {
	Matrix* m = getOneMat();
	Matrix* res = inv(m);
	printMat(res);
	freeMat(&res);
	freeMat(&m);
}

void calAdjMat() {
	Matrix* m = getOneMat();
	Matrix* res = adj(m);
	printMat(res);
	freeMat(&res);
	freeMat(&m);
}

void calTMat() {
	Matrix* m = getOneMat();
	Matrix* res = matT(m);
	printMat(res);
	freeMat(&res);
	freeMat(&m);
}

void calDetMat() {
	Matrix* m = getOneMat();
	double res = det(m);
	printf("\n������ = %lf\n", res);
	freeMat(&m);
}

void matCalculatorRun() {
	while(1) {
		switch(showMenu()) {
			case 1:
				calAddMat();
				break;
			case 2:
				calSubMat();
				break;
			case 3:
				calMulMat();
				break;
			case 4:
				calMulMatNum();
				break;
			case 5:
				calDivMat();
				break;
			case 6:
				calDivMatNum();
				break;
			case 7:
				calInvMat();
				break;
			case 8:
				calDetMat();
				break;
			case 9:
				calAdjMat();
				break;
			case 10:
				calTMat();
				break;
			case 0:
				return;
		}
	}
}
