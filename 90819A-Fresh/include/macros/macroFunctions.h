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
	static void shootOneBallAsync(void *ignore);
	static void shootOneBall();
	static void poopOneBall(void *ignore);
	static void poopTwoBalls(void *ignore);
	static void shootTwoBallsAsync(void *ignore);
};

#endif