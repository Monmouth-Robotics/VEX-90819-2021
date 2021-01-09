#ifndef _DRIVE_CONTROL
#define _DRIVE_CONTROL

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "init/devices.h"
#include "init/display.h"
#include "init/taskManagement.h"
#include "macros/ejectController.h"
#include "macros/shootController.h"
#include "macros/intakeController.h"

using namespace std;

void driveControl();

#endif