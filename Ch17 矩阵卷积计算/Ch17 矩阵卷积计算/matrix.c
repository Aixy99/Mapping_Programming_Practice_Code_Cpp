#include "ch17.h"

void initMat(Matrix* m) {
	for (int i = 0; i < m->row; i++) {
		for (int j = 0; j < m->col; j++) {
			m->mat[i][j] = 0.0;
		}
	}
}

Matrix* creatMatrix(int row, int col) {
	Matrix* m = (Matrix*)malloc(sizeof(Matrix));
	if (!(row && col)) {
		m->row = row;
		m->col = col;
		return m;
	}
	if (!m) return NULL;
	m->mat = (double**)malloc(row * sizeof(double*));
	if (!m->mat) {
		free(m);
		return NULL;
	}
	for (int i = 0; i < row; i++) {
		m->mat[i] = (double*)malloc(col * sizeof(double));
		if (!m->mat[i]) {
			for (int j = 0; j < i; j++) {
				free(m->mat[j]);
			}
			return NULL;
		}
	}

	m->row = row;
	m->col = col;
	initMat(m);
	return m;
}

void freeMatrix(Matrix* m) {
	if (m) {
		if (m->mat) {
			for (int i = 0; i < m->row; i++) {
				if (m->mat[i]) free(m->mat[i]);
			}
			free(m->mat);
		}
		free(m);
	}
}

void printMat(const Matrix* m) {
	if (!m)  return;
	for (int i = 0; i < m->row; i++) {
		for (int j = 0; j < m->col; j++) {
			printf("%-5.2lf ", m->mat[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

Matrix* mulMat(Matrix* m, Matrix* n) {
	Matrix* res = creatMatrix(m->row, n->col);
	if (m->col != n->row) {
		printf("æÿ’Û≤ªƒ‹œ‡≥À\n");
		return res;
	}
	
	for (int i = 0; i < m->row; i++) {
		for (int j = 0; j < n->col; j++) {
			for (int k = 0; k < m->col; k++) {
				res->mat[i][j] += m->mat[i][k] * n->mat[k][j];
			}
		}
	}

	return res;
}