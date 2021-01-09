#ifndef _PROG_SKILLS
#define _PROG_SKILLS

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "init/devices.h"
#include "init/taskManagement.h"
#include "motion/pid.h"
#include "motion/purePursuit/pathGeneration.h"
#include "motion/purePursuit/pathFollowing.h"
#include "macros/ejectController.h"
#include "macros/shootController.h"
#include "macros/intakeController.h"

using namespace std;
using namespace zoo;

static void stopIntakesAsync(void* ignore);
static void stopIntakesAsyncOne(void* ignore);

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
void descoreMiddle();

#endif