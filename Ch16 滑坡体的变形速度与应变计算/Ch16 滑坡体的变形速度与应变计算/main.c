#include "ch16.h"

int main() {
	char* fileName = "../data/�α�۲�����.txt";

	MonitoringData *data = readMonitorDataFile(fileName);
	calSpeed(data);
	calStrain(data);
	free(data);
	return 0;
}