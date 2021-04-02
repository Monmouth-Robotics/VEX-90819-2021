#ifndef _EJECT_CONTROLLER
#define _EJECT_CONTROLLER

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "init/utility.h"
#include "init/devices.h"
#include "macros/indexController.h"
#include "macros/intakeController.h"
#include "positioning/positionController.h"

using namespace std;

class EjectController
{
public:
	EjectController();
	EjectController& withStartCoordinates(double targetStartX, double targetStartY, double distanceStartThreshold);
	EjectController& withStartAngle(double targetStartTheta, double angleStartThreshold);
	EjectController& withEndCoordinates(double targetEndX, double targetEndY, double distanceEndThreshold);
	EjectController& withEndAngle(double targetEndTheta, double angleEndThreshold);
	static void eject(void* ignore);
	static void stopEjecting();

private:
	static bool ejectingStatus;
	static bool hasStartCoordinates;
	static bool hasStartAngle;
	static bool hasEndCoordinates;
	static bool hasEndAngle;
	static double targetStartX;
	static double targetStartY;
	static double targetStartTheta;
	static double targetEndX;
	static double targetEndY;
	static double targetEndTheta;
	static double distanceStartThreshold;
	static double angleStartThreshold;
	static double distanceEndThreshold;
	static double angleEndThreshold;
};

#endif