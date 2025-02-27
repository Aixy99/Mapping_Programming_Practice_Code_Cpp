#include "ch16.h"

int main() {
	char* fileName = "../data/形变观测数据.txt";

	MonitoringData *data = readMonitorDataFile(fileName);
	calSpeed(data);
	calStrain(data);
	free(data);
	return 0;
}