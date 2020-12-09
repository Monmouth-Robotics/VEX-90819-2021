#ifndef _MACRO_FUNCTIONS
#define _MACRO_FUNCTIONS

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"

#include "motion/purePursuit.h"

#include "init/devices.h"

using namespace std;

class MacroFunctions
{
public:
	static void shootOneBall(void* ignore);
	static void shootTwoBalls(void* ignore);
	static void shootThreeBalls(void* ignore);
	static void poopOneBall(void* param);
	static void poopTwoBalls(void* param);
	static void toggleIntakes(int speed);
	static void deploy(void* ignore);
};

#endif