#include "ch14.h"

int main() {
	char* fileName = "../data/时间数据.txt";
	CEArray* ces = creatCEArray(1);
	readCEFile(ces, fileName);
	printJD(ces);
	printCE(ces);
	printDoy(ces);
	printFish(ces);
	freeCEArray(ces);
	return 0;
}