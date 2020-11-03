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
	static void shootOneBall(void *ignore);
	static void shootTwoBalls(void *ignore);
};

#endif