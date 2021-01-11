#ifndef _PID_CONTROLLER
#define _PID_CONTROLLER

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "init/devices.h"
#include "init/utility.h"
#include "positioning/positionController.h"
#include <vector>

using namespace std;

class PIDController {
public:
	PIDController();
	void pidTurn();
	void pidForward();
	void pidBackward();
	void pidRight();
	void pidLeft();
	PIDController& withTargetTheta(double targetTheta);
	PIDController& withDistanceLine(vector<vector<double>> distanceLine);
	PIDController& withLimit(double maxVel);
	PIDController& withTurnGains(double kP, double kI, double kD);
	PIDController& withDistanceGains(double kPDistance, double kIDistance, double kDDistance);
	PIDController& withAngleGains(double kPAngle, double kIAngle, double kDAngle);
	PIDController& withDiffGains(double kPDiff, double kIDiff, double kDDiff);
	PIDController& withMaxDistanceError(double thresholdDistanceError);
	PIDController& withMaxAngleError(double thresholdAngleError);
	PIDController& withMotorStopping(bool stopMotors);
private:
	double targetTheta;
	vector<vector<double>> distanceLine;
	double maxVel;
	double kP;
	double kI;
	double kD;
	double kPDistance;
	double kIDistance;
	double kDDistance;
	double kPAngle;
	double kIAngle;
	double kDAngle;
	double kPDiff;
	double kIDiff;
	double kDDiff;
	double thresholdDistanceError;
	double thresholdAngleError;
	double stopMotors;
};



#endif