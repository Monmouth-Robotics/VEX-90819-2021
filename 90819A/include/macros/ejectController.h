#ifndef _EJECT_CONTROLLER
#define _EJECT_CONTROLLER

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "init/devices.h"
#include "init/taskManagement.h"

using namespace std;

class EjectController
{
public:
	EjectController();
	EjectController& setTopRoller(bool useTopRoller);
	EjectController& withCoordinates(double targetX, double targetY, double distance);
	static void ejectOneBall(void* ignore);
	static void ejectTwoBalls(void* ignore);
	
private:
	static bool ejectingStatus;
	static bool useTopRoller;
	static double targetX;
	static double targetY;
	static bool hasCoordinates;
	static bool hasAngle;
	static double targetX;
	static double targetY;
	static double targetTheta;
	static double distanceThreshold;
	static double angleThreshold;
};

#endif