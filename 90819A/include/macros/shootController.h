#ifndef _SHOOT_CONTROLLER
#define _SHOOT_CONTROLLER

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "init/devices.h"
#include "macros/indexController.h"

using namespace std;

class ShootController
{
public:
	ShootController();
	static void shoot(void* ignore);
};

#endif