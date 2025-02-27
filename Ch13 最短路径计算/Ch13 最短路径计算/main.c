#include "ch13.h"

int main() {
	char* fileName = "../data/路径数据.txt";

	MapArray* mapData = creatMapArray(1);
	readMapFile(mapData, fileName);
	Path* path = creatPath(mapData->size);

	initPath(path);
	map2Path(mapData, path);

	//0       武大    
	//1       地大    
	//2       光谷    
	//3       图书城  
	//4       华工
	printShortPath(path, mapData, 1, 3);

	freePath(path);
	freeMapArray(mapData);
	return 0;
}