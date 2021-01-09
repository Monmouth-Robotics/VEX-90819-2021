#ifndef _EJECT_CONTROLLER
#define _EJECT_CONTROLLER

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "init/devices.h"
#include "init/taskManagement.h"

using namespace std;

namespace zoo {
	class EjectController
	{
	public:
		EjectController();
		EjectController& setTopRoller(bool useTopRoller);
		static void ejectOneBall(void* ignore);
		static void ejectTwoBalls(void* ignore);
	private:
		static bool ejectingStatus;
		static bool useTopRoller;
	};
}

#endif