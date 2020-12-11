#ifndef _PROG_SKILLS
#define _PROG_SKILLS

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "init/devices.h"
#include "motion/pid.h"
#include "motion/purePursuit.h"
#include "macros/macroFunctions.h"
#include "macros/macroInstances.h"

static void stopIntakesAsync(void* ignore);
static void stopIntakesAsyncOne(void *ignore);

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