#ifndef _PID
#define _PID

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "positioning/positionAlg.h"
#include "motion/purePursuit.h"
#include "init/devices.h"
#include <vector>

void pidTurn(double target, double maxVel, double thresholdError, double kP, double kD, double kI);
void pidForward(double targetX, double targetY, double targetTheta, double maxVel, double thresholdDistanceError, double kP, double kPStraight);
void pidForwardBeta(double targetX, double targetY, double targetTheta, double maxVel, double thresholdDistanceError, double kPAngle, double kPDistance, double kPDiff, double kIAngle, double kIDistance, double kIDiff, double kDAngle, double kDDistance, double kDDiff, bool stopMotors);

#endif