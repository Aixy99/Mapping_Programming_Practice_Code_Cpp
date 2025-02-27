#include "ch14.h"

double ce2jd(CE ce) {
	double jd = 0.0;
	jd = 1721013.5 + 367 * ce.year -
		(int)((7.0 / 4.0) * (ce.year + (int)((ce.month + 9) / 12))) +
		(int)(275 * ce.month / 9.0) + ce.day + ce.hour / 24.0 +
		ce.minutes / 1440.0 + ce.second / 86400.0;
	return jd;
}