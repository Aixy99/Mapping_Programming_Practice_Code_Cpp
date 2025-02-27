#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	int row;
	int col;
	double** mat;
} Matrix;

Matrix* creatMat(int row, int col);
void printMat(Matrix* m);
void freeMat(Matrix* m);
Matrix* addMat(Matrix* m, Matrix* n);
Matrix* subMat(Matrix* m, Matrix* n);
Matrix* mulMat(Matrix* m, Matrix* n);
Matrix* mulMatNum(Matrix* m, double num);
double det(Matrix* m);
Matrix* adj(Matrix* m);
Matrix* matT(Matrix* m);
Matrix* matcpy(Matrix* m);
Matrix* inv(Matrix* m);
Matrix* divMat(Matrix* m, Matrix* n);
Matrix* divMatNum(Matrix* m, double num);

void matCalculatorRun();
#endif // !MATRIX_H
