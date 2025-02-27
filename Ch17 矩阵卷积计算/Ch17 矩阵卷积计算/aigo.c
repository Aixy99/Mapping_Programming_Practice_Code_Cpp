#include "ch17.h"

int judgeM(int I, int J, int i, int j) {
	if (I - i - 1 < 0 ||
		J - j - 1 < 0 ||
		I - i - 1 > 9 ||
		J - j - 1 > 9) {
		return 1;
	}
	return 0;
}

double cal1(Matrix* m, Matrix* n, int I, int J) {
	double up = 0.0;
	double down = 0.0;
	double res = 0.0;

	

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (judgeM(I, J, i, j)) {
				up += 0;
				continue;
			}
			up += m->mat[i][j] * n->mat[I - i - 1][J - j - 1];
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (judgeM(I, J, i, j)) {
				up += 0;
				continue;
			}
			down += m->mat[i][j];
		}
	}
	
	if (down == 0.0) {
		res = nanf(" ");
	} else {
		res = up / down;	res = up / down;
	}
	return res;
}

double cal2(Matrix* m, Matrix* n, int I, int J) {
	double up = 0.0;
	double down = 0.0;
	double res = 0.0;



	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (judgeM(I, J, i, j)) {
				up += 0;
				continue;
			}
			up += m->mat[i][j] * n->mat[9 - (I - i - 1)][9 - (J - j - 1)];
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (judgeM(I, J, i, j)) {
				up += 0;
				continue;
			}
			down += m->mat[i][j];
		}
	}

	if (down == 0.0) {
		res = nanf(" ");
	} else {
		res = up / down;	res = up / down;
	}
	return res;
}

Matrix* aigo1(Matrix* m, Matrix* n) {
	Matrix* res = creatMatrix(n->row, n->col);
	for (int i = 0; i < res->row; i++) {
		for (int j = 0; j < res->col; j++) {
			res->mat[i][j] = cal1(m, n, i, j);
		}
	}
	return res;
}

Matrix* aigo2(Matrix* m, Matrix* n) {
	Matrix* res = creatMatrix(n->row, n->col);
	for (int i = 0; i < res->row; i++) {
		for (int j = 0; j < res->col; j++) {
			res->mat[i][j] = cal2(m, n, i, j);
		}
	}
	return res;
}