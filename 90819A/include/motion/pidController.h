#ifndef _PID_CONTROLLER
#define _PID_CONTROLLER

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "init/devices.h"
#include "init/utility.h"
#include "init/taskManagement.h"
#include <vector>

using namespace std;

namespace zoo {
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
		static double targetTheta;
		static vector<vector<double>> distanceLine;
		static double maxVel;
		static double kP;
		static double kI;
		static double kD;
		static double kPDistance;
		static double kIDistance;
		static double kDDistance;
		static double kPAngle;
		static double kIAngle;
		static double kDAngle;
		static double kPDiff;
		static double kIDiff;
		static double kDDiff;
		static double thresholdDistanceError;
		static double thresholdAngleError;
		static double stopMotors;
	};
}



#endif