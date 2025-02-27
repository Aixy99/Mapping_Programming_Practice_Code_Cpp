#include "ch17.h"

int main() {
	char* nMatFileName = "C:/MyFIles/AboutCode/Cpp/practice/Ch17 ¾ØÕó¾í»ı¼ÆËã/data/N¾ØÕó.txt";
	char* mMatFileName = "C:/MyFIles/AboutCode/Cpp/practice/Ch17 ¾ØÕó¾í»ı¼ÆËã/data/M¾ØÕó.txt";

	Matrix* m = reatMatFile(mMatFileName);
	Matrix* n = reatMatFile(nMatFileName);

	Matrix* res1 = aigo1(m, n);
	Matrix* res2 = aigo2(m, n);

	printf("------------------------Ëã·¨1-------------------------\n");
	printMat(res1);

	printf("------------------------Ëã·¨2-------------------------\n");
	printMat(res2);

	freeMatrix(m);
	freeMatrix(n);
	freeMatrix(res1);
	freeMatrix(res2);

	return 0;
}