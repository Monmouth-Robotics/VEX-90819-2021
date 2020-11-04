#ifndef _INDEXING
#define _INDEXING

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"

#include "init/devices.h"

using namespace std;

class Indexing
{
public:
	static void indexingTask(void *ignore);
	static void shootBall();
	static bool getTopStatus();
	static bool getBottomStatus();
	static void setTopStatus(bool);
	static void setBottomStatus(bool);
	static int getBaseTop();
	static int getBaseBottom();
};

#endif