#ifndef _INDEX_CONTROLLER
#define _INDEX_CONTROLLER

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"

#include "init/devices.h"

using namespace std;

class IndexController
{
public:
	static void indexingTask(void* ignore);
	static char* getTopStatus();
	static char* getBottomStatus();
	static char* getBackStatus();
	static char* getIntakeColor();
	static void toggleTop(bool disabled);
	static void toggleBottom(bool disabled);
	static void toggleTopPosition(bool disabled);
private:
	static char* topBallDetected;
	static char* bottomBallDetected;
	static char* backBallDetected;
	static char* intakeBallColor;
	static bool topDisabled;
	static bool topPositionDisabled;
	static bool bottomDisabled;
};

#endif