#ifndef _PROG_SKILLS
#define _PROG_SKILLS

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "init/devices.h"
#include "init/taskManagement.h"
#include "motion/purePursuit/pathFollowing.h"
#include "motion/pidController.h"
#include "macros/ejectController.h"
#include "macros/shootController.h"
#include "macros/intakeController.h"

using namespace std;
using namespace zoo;

void runProgSkills();
void firstGoal(IntakeController intakeController);
void secondGoal(IntakeController intakeController);
void thirdGoal(IntakeController intakeController);
void fourthGoal(IntakeController intakeController);
void fifthGoal(IntakeController intakeController);
void sixthGoal(IntakeController intakeController);
void seventhGoal(IntakeController intakeController);
void eighthGoal(IntakeController intakeController);
void ninthGoal(IntakeController intakeController);

#endif