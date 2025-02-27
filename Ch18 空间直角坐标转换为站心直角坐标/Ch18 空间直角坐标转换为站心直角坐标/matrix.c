#include "ch18.h"

void initMat(Matrix* m) {
	if (!m->mat) {
		m->col = 0;
		m->row = 0;
	}
	for (int i = 0; i < m->row; i++) {
		for (int j = 0; j < m->col; j++) {
			m->mat[i][j] = 0.0;
		}
	}
}

Matrix* creatMat(int row, int col) {
	Matrix* m = (Matrix*)malloc(sizeof(Matrix));
	m->row = row;
	m->col = col;

	if (!(col && row)) {
		printf("row or col cant equal 0\n");
		return m;
	}

	m->mat = (double**)malloc(sizeof(double*) * row);
	for (int i = 0; i < row; i++) {
		m->mat[i] = (double*)malloc(sizeof(double) * col);
	}
	initMat(m);
	return m;
}

void printMat(Matrix* m) {
	for (int i = 0; i < m->row; i++) {
		for (int j = 0; j < m->col; j++) {
			printf("%lf ", m->mat[i][j]);
		}
		printf("\n");
	}
}

void freeMat(Matrix* m) {
	if (m->col && m->row) {
		for (int i = 0; i < m->row; i++) {
			free(m->mat[i]);
		}
		free(m->mat);
	}
	free(m);
}

Matrix* subMat(Matrix* m, Matrix* n) {
	if (!m || !n) return NULL;

	if (!(m->col == n->col) || !(m->row == n->row)) {
		printf("矩阵减法失败，行列必须相同\n");
		return NULL;
	}

	Matrix* res = creatMat(m->row, m->col);
	for (int i = 0; i < res->row; i++) {
		for (int j = 0; j < res->col; j++) {
			res->mat[i][j] = m->mat[i][j] - n->mat[i][j];
		}
	}
	return res;
}

Matrix* mulMat(Matrix* m, Matrix* n) {
	if (!m || !n) return NULL;

	if (m->col != n->row) {
		printf("矩阵乘法失败，m 的列和n 的行必须相同\n");
		return NULL;
	}


	Matrix* res = creatMat(m->row, n->col);
	for (int i = 0; i < res->row; i++) {
		for (int j = 0; j < res->col; j++) {
			for (int k = 0; k < m->col; k++) {
				res->mat[i][j] += m->mat[i][k] * n->mat[k][j];
			}
		}
	}

	return res;
}