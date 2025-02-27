#include "ch13.h"

int main() {
	char* fileName = "../data/·������.txt";

	MapArray* mapData = creatMapArray(1);
	readMapFile(mapData, fileName);
	Path* path = creatPath(mapData->size);

	initPath(path);
	map2Path(mapData, path);

	//0       ���    
	//1       �ش�    
	//2       ���    
	//3       ͼ���  
	//4       ����
	printShortPath(path, mapData, 1, 3);

	freePath(path);
	freeMapArray(mapData);
	return 0;
}