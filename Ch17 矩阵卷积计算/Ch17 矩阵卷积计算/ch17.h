#ifndef CH17_H
#define CH17_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
	double** mat;
	int row;
	int col;
} Matrix;

Matrix* creatMatrix(int row, int col);
void freeMatrix(Matrix* m);
void printMat(const Matrix* m);
void initMat(Matrix* m);
Matrix* reatMatFile(char* fileName);
Matrix* aigo1(Matrix* m, Matrix* n);
Matrix* mulMat(Matrix* m, Matrix* n);
Matrix* aigo2(Matrix* m, Matrix* n);
#endif // !CH17_H
