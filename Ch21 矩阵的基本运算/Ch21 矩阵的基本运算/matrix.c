#include "matrix.h"

Matrix* creatMat(int row, int col) {
	if(row <= 0 || col <= 0) {
		printf("行和列不能为零或负数\n");
		return NULL;
	}
	Matrix* m = (Matrix*)malloc(sizeof(Matrix));

	if(!m) {
		printf("Matrix creat failure\n");
		return NULL;
	}

	m->mat = (double**)malloc(sizeof(double*) * row);
	
	if(!m->mat) {
		printf("Matrix creat failure\n");
		free(m);
		return NULL;
	}

	for(int i = 0; i < row; i++) {
		m->mat[i] = (double*)malloc(sizeof(double) * col);

		if(!m->mat[i]) {
			printf("Matrix creat failure\n");

			for(int j = 0; j < i; j++) {
				free(m->mat[j]);
			}
			free(m);
			return NULL;
		}
	}

	for(int i = 0; i < row; i++) {
		for(int j = 0; j < col; j++) {
			m->mat[i][j] = 0.0;
		}
	}

	m->row = row;
	m->col = col;
	return m;
}

void printMat(Matrix* m) {
	if(!m) {
		printf("矩阵不能为空\n");
		return;
	}
	printf("\n----------------------------------------\n");
	for(int i = 0; i < m->row; i++) {
		for(int j = 0; j < m->col; j++) {
			printf("%.3lf ", m->mat[i][j]);
		}
		printf("\n");
	}
	printf("----------------------------------------\n\n");
}

void freeMat(Matrix** m) { 
	if(m && *m) {         
		Matrix* mat_ptr = *m; 
		if(mat_ptr->mat) {
			for(int i = 0; i < mat_ptr->row; i++) {
				if(mat_ptr->mat[i]) {
					free(mat_ptr->mat[i]);
				}
			}
			free(mat_ptr->mat);
		}
		free(mat_ptr);
		*m = NULL; 
	}
}

Matrix* addMat(Matrix* m, Matrix* n) {
	if(!m || !n) {
		printf("矩阵不能为空\n");
		return NULL;
	}
	if(m->row != n->row || m->col != n->col) {
		printf("矩阵的行列必须相等\n");
		return NULL;
	}

	Matrix* res = creatMat(m->row, m->col);

	for(int i = 0; i < m->row; i++) {
		for(int j = 0; j < m->col; j++) {
			res->mat[i][j] = m->mat[i][j] + n->mat[i][j];
		}
	}

	return res;
}

Matrix* subMat(Matrix* m, Matrix* n) {
	if(!m || !n) {
		printf("矩阵不能为空\n");
		return NULL;
	}
	if(m->row != n->row || m->col != n->col) {
		printf("矩阵的行列必须相等\n");
		return NULL;
	}

	Matrix* res = creatMat(m->row, m->col);

	for(int i = 0; i < m->row; i++) {
		for(int j = 0; j < m->col; j++) {
			res->mat[i][j] = m->mat[i][j] - n->mat[i][j];
		}
	}

	return res;
}

Matrix* mulMat(Matrix* m, Matrix* n) {
	if(!m || !n) {
		printf("矩阵不能为空\n");
		return NULL;
	}
	if(m->col != n->row) {
		printf("矩阵1的列必须等于矩阵2的行\n");
		return NULL;
	}

	Matrix* res = creatMat(m->row, n->col);

	for(int i = 0; i < m->row; i++) {
		for(int j = 0; j < m->col; j++) {
			for(int k = 0; k < m->col; k++) {
				res->mat[i][j] += m->mat[i][k] * n->mat[k][j];
			}
		}
	}

	return res;
}

Matrix* mulMatNum(Matrix* m, double num) {
	if(!m) {
		printf("矩阵不能为空\n");
		return NULL;
	}

	Matrix* res = creatMat(m->row, m->col);

	for(int i = 0; i < m->row; i++) {
		for(int j = 0; j < m->col; j++) {
			res->mat[i][j] = m->mat[i][j] * num;
		}
	}

	return res;
}

Matrix* cof(Matrix* m, int a, int b) { // 获得余子式
	Matrix* res = creatMat(m->row - 1, m->col - 1);
	for(int i = 0; i < res->row; i++) {
		for(int j = 0; j < res->col; j++) {
			if(i < a) {
				if(j < b) {
					res->mat[i][j] = m->mat[i][j];
				} else {
					res->mat[i][j] = m->mat[i][j + 1];
				}
			} else {
				if(j < b) {
					res->mat[i][j] = m->mat[i + 1][j];
				} else {
					res->mat[i][j] = m->mat[i + 1][j + 1];
				}
			}
		}
	}

	return res;
}

double det(Matrix* m) { // 求行列式
	double res = 0.0;
	//printMat(m);
	if(!m || !m->row || !m->col) {
		printf("矩阵不能为空或行列数不能为0\n");
		return res;
	}
	if(m->row != m->col) {
		printf("行列式计算必须为方阵\n");
		return res;
	}

	if(m->row == 1) {
		res = m->mat[0][0];
		return res;
	}

	Matrix** n = (Matrix**)malloc(sizeof(Matrix*) * m->col);

	for(int i = 0; i < m->col; i++) {
		n[i] = cof(m, 0, i);
		res += m->mat[0][i] * pow(-1, 1 + i + 1) * det(n[i]);
		freeMat(&n[i]);
	} 
	free(n);
	return res;
}

Matrix* adj(Matrix* m) { // 伴随矩阵
	if(!m || !m->row || !m->col) {
		printf("矩阵不能为空或行列数不能为0\n");
		return NULL;
	}
	if(m->row != m->col) {
		printf("行列式计算必须为方阵\n");
		return NULL;
	}

	Matrix* res = creatMat(m->row, m->col);

	for(int i = 0; i < res->row; i++) {
		for(int j = 0; j < res->col; j++) {
			Matrix* c = cof(m, i, j);
			res->mat[i][j] = pow(-1, i + j) * det(c);
			freeMat(&c);
		}
	}

	Matrix* result = matT(res);

	freeMat(&res);

	return result;
}

Matrix* matT(Matrix* m) { // 矩阵转置
	if(!m || !m->row || !m->col) {
		printf("矩阵不能为空或行列数不能为0\n");
		return NULL;
	}

	Matrix* res = matcpy(m);

	for(int i = 0; i < res->row; i++) {
		for(int j = 0; j < res->col; j++) {
			if(i == j) break;
			double temp = res->mat[i][j];
			res->mat[i][j] = res->mat[j][i];
			res->mat[j][i] = temp;
		}
	}

	return res;
}

Matrix* matcpy(Matrix* m) {
	if(!m || !m->row || !m->col) {
		printf("矩阵不能为空或行列数不能为0\n");
		return NULL;
	}

	Matrix* res = creatMat(m->row, m->col);
	for(int i = 0; i < res->row; i++) {
		for(int j = 0; j < res->col; j++) {
			res->mat[i][j] = m->mat[i][j];
		}
	}

	return res;
}

Matrix* inv(Matrix* m) {
	if(!m || !m->row || !m->col) {
		printf("矩阵不能为空或行列数不能为0\n");
		return NULL;
	}
	if(m->row != m->col) {
		printf("行列式计算必须为方阵\n");
		return NULL;
	}
	if(!det(m)) {
		printf("矩阵行列式为零，不存在逆矩阵\n");
		return NULL;
	}

	Matrix* adjM = adj(m);
	Matrix* res = mulMatNum(adjM, 1.0 / det(m));

	return res;
}

Matrix* divMat(Matrix* m, Matrix* n) {
	if(!m || !n) {
		printf("矩阵不能为空\n");
		return NULL;
	}
	if(m->row != n->col) {
		printf("矩阵1的行必须等于矩阵2的列\n");
		return NULL;
	}

	Matrix* n_inv = inv(n);
	Matrix* res = mulMat(m, n_inv);
	freeMat(&n_inv);

	return res;
}

Matrix* divMatNum(Matrix* m, double num) {
	if(!m) {
		printf("矩阵不能为空\n");
		return NULL;
	}

	Matrix* res = creatMat(m->row, m->col);

	for(int i = 0; i < m->row; i++) {
		for(int j = 0; j < m->col; j++) {
			res->mat[i][j] = m->mat[i][j] / num;
		}
	}

	return res;
}