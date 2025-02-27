#ifndef CH13_H
#define CH13_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
	int num;
	_Bool isFinal;
	char name[30];
	int distance;
	int before;
} Spot;

typedef struct {
	Spot* data;
	int size;
	int capacity;
} Path;

typedef struct {
	char start[30];
	char end[30];
	int distance;
} Map;

typedef struct {
	Map* data;
	int size;
	int capacity;
} MapArray;

Path* creatPath(int initialCapacity);
MapArray* creatMapArray(int initialCapacity);
void freeMapArray(MapArray* mapData);
void freePath(Path* path);
void readMapFile(MapArray* mapData, char* fileName);
void initPath(Path* path);
void showPath(Path* path);
void map2Path(MapArray* map, Path* path);
void showMap(const MapArray* map);
void shortPath(MapArray* map, Path* path, char* start);
void printShortPath(Path* path, MapArray* map, int start, int end);
#endif // !CH13_H

