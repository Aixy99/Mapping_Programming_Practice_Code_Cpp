#include "matrix.h"
int getIntNum() {
	int num = 0;

	while(scanf("%d", &num) != 1) {
		printf("输入有误，请重新输入\n");

		int c;
		while((c = getchar()) != '\n' && c != EOF); // 清除缓存区
	}
	return num;
}

double getDoubleNum() {
	double num = 0;

	while(scanf("%lf", &num) != 1) {
		printf("输入有误，请重新输入\n");

		int c;
		while((c = getchar()) != '\n' && c != EOF); // 清除缓存区
	}
	return num;
}

int getRowOrCol() {
	int num = getIntNum();

	while(num < 1) {
		printf("必须大于0，请重新输入\n");
		num = getIntNum();
	}
	return num;
}

Matrix* getMat(int row, int col) {
	Matrix* m = creatMat(row, col);
	
	int count = 0;
	for(int i = 0; i < m->row; i++) {
		for(int j = 0; j < m->col; j++) {
			printf("请输入第 %d 个数：", ++count);
			m->mat[i][j] = getDoubleNum();
		}
	}
	return m;
}

Matrix** getTwoMat() {
	int row = 0;
	int col = 0;

	printf("请输入矩阵行数:\n");
	row = getRowOrCol();
	printf("请输入矩阵列数:\n");
	col = getRowOrCol();

	Matrix** m = (Matrix**)malloc(sizeof(Matrix*) * 2);
	printf("----------矩阵 1----------\n");
	m[0] = getMat(row, col);
	printf("-------------------------\n");
	printf("----------矩阵 2----------\n");
	m[1] = getMat(row, col);
	printf("-------------------------\n");

	return m;
}

Matrix* getOneMat() {
	int row = 0;
	int col = 0;

	printf("请输入矩阵行数:\n");
	row = getRowOrCol();
	printf("请输入矩阵列数:\n");
	col = getRowOrCol();

	Matrix* m = getMat(row, col);

	return m;
}

int showMenu() {
	printf("-------------------矩阵计算器-------------------\n");
	printf("                 1  矩阵相加\n");
	printf("                 2  矩阵相减\n");
	printf("                 3  矩阵相乘\n");
	printf("                 4  矩阵与数相乘\n");
	printf("                 5  矩阵相除\n");
	printf("                 6  矩阵与数相除\n");
	printf("                 7  矩阵的逆\n");
	printf("                 8  求行列式\n");
	printf("                 9  求伴随矩阵\n");
	printf("                 10 矩阵转置\n");
	printf("                 0  退出\n");
	printf("------------------------------------------------\n");
	printf("请选择你要进行的计算（0-10）:");
	int select = getIntNum();
	while(select > 10 || select < 0) {
		printf("输入有误，请输入（0-10）\n");
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
	printf("请输入数字\n");
	double num = getDoubleNum();
	Matrix* res = mulMatNum(m, num);
	printMat(res);
	freeMat(&res);
	freeMat(&m);
}

void calDivMatNum() {
	Matrix* m = getOneMat();
	printf("请输入数字\n");
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
	printf("\n计算结果 = %lf\n", res);
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
