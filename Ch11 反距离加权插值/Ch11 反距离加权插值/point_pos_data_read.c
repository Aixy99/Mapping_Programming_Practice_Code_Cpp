#include "Ch11.h"

/*
* 创建测点位置数组
* 
* return : PosArray数组
*		   NULL
*/
PosArray* createPosArray(int initialCapacity) {
	PosArray* posData = (PosArray*)malloc(sizeof(PosArray));
	if (posData == NULL) return NULL;
	posData->data = (Pos*)malloc(initialCapacity * sizeof(Pos));
	if (posData->data == NULL) {
		free(posData);
		return NULL;	
	}
	posData->size = 0;
	posData->capacity = initialCapacity;
	return posData;
}

/*
* 释放测点位置数组
*/
void freePosArray(PosArray* posData) {
	if (posData != NULL) {
		if (posData->data != NULL) {
			free(posData->data);
		}
		free(posData);
	}
}

int readPosData(char* file, PosArray* posData) {
	FILE* fp = fopen(file, "r");
	if (fp == NULL) {
		printf("data文件打开失败！\n");
		return 1;
	}

	char buff[256] = { 0 };
	char pointName[10] = { 0 };
	double x = 0.0;
	double y = 0.0;
	double h = 0.0;

	while (fgets(buff, sizeof(buff), fp)) {
		// 扩容
		if (posData->size >= posData->capacity) {
			int newCapacity = posData->capacity * 2;
			Pos* newPosData = (Pos*)realloc(posData->data, 
				sizeof(Pos) * newCapacity);
			if (newPosData == NULL) {
				printf("内存分配失败\n");
				return 2;
			}
			posData->data = newPosData;	
			posData->capacity = newCapacity;
		}

		if (sscanf(buff,
			"%9[^,],%lf,%lf,%lf",
			pointName,
			&x,
			&y,
			&h) != 4) {
			printf("行格式有误: %s\n", buff);
			continue;
		} else {
			memcpy(posData->data[posData->size].pointName, pointName, 9);
			posData->data[posData->size].x = x;
			posData->data[posData->size].y = y;
			posData->data[posData->size].h = h;
			posData->size++;
		}

	}
	return 0;
}