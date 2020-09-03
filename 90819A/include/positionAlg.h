#ifndef _POSITION_ALG
#define _POSITION_ALG

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
#include "devices.h"
#include <vector>

using namespace std;

class PositionAlg {
public:
	static void calcPosition(void* ignore);
	static vector<double> getPosition(void);
	static void resetGlobal(void);
	static double getTheta(void);
};

#endif
