#include "ch13.h"

void initPath(Path* path) {
	for (int i = 0; i < path->capacity; i++) {
		path->data[i].num = i;
		path->data[i].before = -1;
		path->data[i].isFinal = 0;
		path->data[i].distance = 999999999;
		memcpy(path->data[i].name, "无", 10);
	}
}

void showPath(Path* path) {
	printf("---------------------------------------------\n");
	printf("序号\t名称\t找到\t距离\t\t前面点序号\n");
	printf("---------------------------------------------\n");
	for (int i = 0; i < path->size; i++) {
		printf("%d\t%s\t%d\t%-9d\t%d\n",
			path->data[i].num,
			path->data[i].name,
			path->data[i].isFinal,
			path->data[i].distance,
			path->data[i].before);
	}
}

void map2Path(MapArray* map, Path* path) {
	char name[10] = { 0 };
	int isSame = 0;
	for (int i = 0; i < map->size * 2; i++) {
		isSame = 0;
		if (i >= map->size) {
			memcpy(name, map->data[i - 10].end, 10);
		} else {
			memcpy(name, map->data[i].start, 10);
		}
		for (int j = 0; j < path->capacity; j++) {
			if (!strcmp(name, path->data[j].name)) {
				isSame = 1;
				break;
			}
		}
		if (isSame) continue;
		memcpy(path->data[path->size++].name, name, 10);
	}
}

int getDistance(MapArray* map, char* start, char* end) {
	if (!strcmp(start, end)) return 0;
	for (int i = 0; i < map->size; i++) {
		if (!strcmp(start, map->data[i].start)) {
			for (int j = 0; j < map->size; j++) {
				if (!strcmp(end, map->data[j].end) && i == j) {
					return map->data[i].distance;
				}
			}
		}
	}
	return -1;
}

int getNum(Path* path, char* name) {
	for (int i = 0; i < path->size; i++) {
		if (!strcmp(name, path->data[i].name)) {
			return path->data[i].num;
		}
	}
	return -1;
}

int getMinDistanceSpotNum(Path* path) {
	int minSpotNum = -1;
	int min = 999999999;
	for (int i = 0; i < path->size; i++) {
		if (path->data[i].distance < min && !path->data[i].isFinal) {
			min = path->data[i].distance;
			minSpotNum = path->data[i].num;
		}
	}
	return minSpotNum;
}

void shortPath(MapArray* map, Path* path, char* start) {
	int distance = 999999999;
	for (int i = 0; i < path->size; i++) {
		if (!strcmp(start, path->data[i].name) && !path->data[i].isFinal) {
			path->data[i].distance = 0;
			path->data[i].isFinal = 1;
		}
		int dis = getDistance(map, start, path->data[i].name);
		if (dis > 0 && !path->data[i].isFinal) {
				dis += path->data[getNum(path,start)].distance;
			if (dis < path->data[i].distance) {
				path->data[i].distance = dis;
				path->data[i].before = getNum(path, start);
			}
		}
	}
	showPath(path);
	int minDistanceSpotNum = getMinDistanceSpotNum(path);
	if (minDistanceSpotNum != -1) {
		path->data[minDistanceSpotNum].isFinal = 1;
		shortPath(map, path, path->data[minDistanceSpotNum].name);
	}
}

void printShortPath(Path* path, MapArray* map, int start, int end) {
	shortPath(map, path, path->data[start].name);

	printf("\n\n\n--------------------- %s 到 %s 最短路径-----------------------\n",
		path->data[start].name, path->data[end].name);
	int currentSpot = end;
	printf("%s ", path->data[currentSpot].name);
	while (path->data[currentSpot].before != -1) {
		printf("<--%d-- %s ",
			getDistance(map,path->data[path->data[currentSpot].before].name,
				path->data[currentSpot].name),
			path->data[path->data[currentSpot].before].name);
		currentSpot = path->data[currentSpot].before;
	}
	printf("\n--------------------------------------------------------------------");
}