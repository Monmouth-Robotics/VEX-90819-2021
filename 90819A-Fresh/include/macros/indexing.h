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
	static string getTopStatus();
	static string getBottomStatus();
	static void toggleTop(bool disabled);
	static void toggleBottom(bool disabled);
};

#endif