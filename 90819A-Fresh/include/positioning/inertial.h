#ifndef _INERTIAL
#define _INERTIAL

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
#include "init/devices.h"

using namespace std;

class Inertial
{
public:
	static bool initialize();
	static void calcAngle(void* ignore);
	static void reset(void);
	static double getTheta(void);
};

#endif
