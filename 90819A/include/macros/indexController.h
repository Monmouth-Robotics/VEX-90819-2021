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
	static char* getTopColor();
	static char* getIntakeColor();
	static void toggleIndexing(bool disabled);
private:
	static char* topBallColor;
	static char* intakeBallColor;
	static bool indexDisabled;
};

#endif