#include "ch13.h"

Path* creatPath(int initialCapacity) {
	Path* path = (Path*)malloc(sizeof(Path));
	if (path == NULL) return NULL;
	path->data = (Spot*)malloc(sizeof(Spot) * initialCapacity);
	if (path->data == NULL) {
		free(path);
		return NULL;
	}
	path->size = 0;
	path->capacity = initialCapacity;
}

MapArray* creatMapArray(int initialCapacity) {
	MapArray* mapData = (MapArray*)malloc(sizeof(MapArray));
	if (mapData == NULL) return NULL;
	mapData->data = (Map*)malloc(sizeof(Map) * initialCapacity);
	if (mapData->data == NULL) {
		free(mapData);
		return NULL;
	}
	mapData->size = 0;
	mapData->capacity = initialCapacity;
}

void freeMapArray(MapArray* mapData) {
	if (mapData != NULL) {
		if (mapData->data != NULL) {
			free(mapData->data);
		}
		free(mapData);
	}
}

void freePath(Path* path) {
	if (path != NULL) {
		if (path->data != NULL) {
			free(path->data);
		}
		free(path);
	}
}

void readMapFile(MapArray* mapData, char* fileName) {
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("File open failure\n");
	}

	char buffer[256] = { 0 };
	char* fields[20];
	int distance = 0;

	while (fgets(buffer, 256, fp)) {
		// À©ÈÝ
		if (mapData->size >= mapData->capacity) {
			int newCapacity = mapData->capacity * 2;
			Map* newData = (Map*)realloc(mapData->data,
				sizeof(Map) * newCapacity);
			if (newData == NULL) {
				printf("À©ÈÝÊ§°Ü£ºsize = %d\n", mapData->size);
			}
			mapData->data = newData;
			mapData->capacity = newCapacity;
		}

		// ·Ö¸î×Ö·û´®¶ÁÈ¡
		int count = 0;
		char* token = strtok(buffer, ",");
		while (token != NULL && count < 3) {
			fields[count++] = token;
			token = strtok(NULL, ",");
		}
		
		if (count == 3) {
			memcpy(mapData->data[mapData->size].start, fields[0], 20);
			memcpy(mapData->data[mapData->size].end, fields[1], 20);
			if (sscanf(fields[2], "%d", &distance) == 1) {
				mapData->data[mapData->size++].distance = distance;
			}
		}
	}
}

void showMap(const MapArray* map) {
	for (int i = 0; i < map->size; i++) {
		printf("%s\t%s\t%d\n",
			map->data[i].start,
			map->data[i].end,
			map->data[i].distance);
	}
}