#ifndef _OKAPI
#define _OKAPI

#include "api.h"
#include "okapi/api.hpp"
#include <vector>

using namespace okapi;

extern std::shared_ptr<OdomChassisController> chassis;
extern std::shared_ptr<ChassisController> chassisStrafe;

#endif