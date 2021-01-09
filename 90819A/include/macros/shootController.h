#ifndef _SHOOT_CONTROLLER
#define _SHOOT_CONTROLLER

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "init/devices.h"
#include "init/taskManagement.h"

using namespace std;

namespace zoo {
	class ShootController
	{
	public:
		ShootController();
		static void shootPowerful(void* ignore);
		static void shootTwoBalls(void* ignore);
		static void shootOneBall(void* ignore);
	};
}

#endif