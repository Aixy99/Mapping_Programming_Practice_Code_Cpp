#include "ch17.h"

int main() {
	char* nMatFileName = "C:/MyFIles/AboutCode/Cpp/practice/Ch17 ����������/data/N����.txt";
	char* mMatFileName = "C:/MyFIles/AboutCode/Cpp/practice/Ch17 ����������/data/M����.txt";

	Matrix* m = reatMatFile(mMatFileName);
	Matrix* n = reatMatFile(nMatFileName);

	Matrix* res1 = aigo1(m, n);
	Matrix* res2 = aigo2(m, n);

	printf("------------------------�㷨1-------------------------\n");
	printMat(res1);

	printf("------------------------�㷨2-------------------------\n");
	printMat(res2);

	freeMatrix(m);
	freeMatrix(n);
	freeMatrix(res1);
	freeMatrix(res2);

	return 0;
}