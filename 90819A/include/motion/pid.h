#ifndef _PID
#define _PID

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "positioning/positionAlg.h"
#include "motion/purePursuit/purePursuitOld.h"
#include "init/devices.h"
#include <vector>

void pidTurn(double target, double maxVel, double thresholdError, double kP, double kD, double kI);
void pidForward(double targetTheta, vector<vector<double>> distanceLine, double maxVel, double thresholdDistanceError, double kPAngle, double kPDistance, double kPDiff, double kIAngle, double kIDistance, double kIDiff, double kDAngle, double kDDistance, double kDDiff, bool stopMotors);
void pidBackward(double targetTheta, vector<vector<double>> distanceLine, double maxVel, double thresholdDistanceError, double kPAngle, double kPDistance, double kPDiff, double kIAngle, double kIDistance, double kIDiff, double kDAngle, double kDDistance, double kDDiff, bool stopMotors);
void pidRight(double targetTheta, vector<vector<double>> distanceLine, double maxVel, double thresholdDistanceError, double kPAngle, double kPDistance, double kPDiff, double kIAngle, double kIDistance, double kIDiff, double kDAngle, double kDDistance, double kDDiff, bool stopMotors);
void pidLeft(double targetTheta, vector<vector<double>> distanceLine, double maxVel, double thresholdDistanceError, double kPAngle, double kPDistance, double kPDiff, double kIAngle, double kIDistance, double kIDiff, double kDAngle, double kDDistance, double kDDiff, bool stopMotors);

#endif