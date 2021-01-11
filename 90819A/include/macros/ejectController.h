#ifndef _EJECT_CONTROLLER
#define _EJECT_CONTROLLER

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "init/utility.h"
#include "init/devices.h"
#include "macros/indexController.h"
#include "positioning/positionController.h"

using namespace std;

class EjectController
{
public:
	EjectController();
	EjectController& setTopRoller(bool useTopRoller);
	EjectController& withCoordinates(double targetX, double targetY, double distanceThreshold);
	EjectController& withAngle(double targetTheta, double angleThreshold);
	static void ejectOneBall(void* ignore);
	static void ejectTwoBalls(void* ignore);
	
private:
	static bool ejectingStatus;
	static bool useTopRoller;
	static bool hasCoordinates;
	static bool hasAngle;
	static double targetX;
	static double targetY;
	static double targetTheta;
	static double distanceThreshold;
	static double angleThreshold;
};

#endif