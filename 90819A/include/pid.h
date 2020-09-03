#ifndef _PID
#define _PID

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "positionAlg.h"
#include "purePursuit.h"
#include "devices.h"
#include <vector>

void pidTurn(double target, double maxVel, double thresholdError, double kP, double kD, double kI);
void pidForward(double targetX, double targetY, double targetTheta, double maxVel, double thresholdDistanceError, double kP, double kPStraight);

#endif