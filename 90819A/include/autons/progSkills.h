#ifndef _PROG_SKILLS
#define _PROG_SKILLS

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "init/devices.h"
#include "motion/purePursuit/pathFollowing.h"
#include "motion/pidController.h"
#include "macros/ejectController.h"
#include "macros/shootController.h"
#include "macros/intakeController.h"
#include "macros/IndexController.h"
#include "positioning/positionController.h"

using namespace std;

void runProgSkills();
void firstGoal();
void secondGoal();
void thirdGoal();
void fourthGoal();
void fifthGoal();
void sixthGoal();
void seventhGoal();
void eighthGoal();
void ninthGoal();

#endif