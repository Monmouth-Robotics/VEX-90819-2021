#include "macros/ejectController.h"

bool EjectController::ejectingStatus = false;
bool EjectController::hasCoordinates = false;
bool EjectController::hasAngle = false;
double EjectController::targetX = 0.0;
double EjectController::targetY = 0.0;
double EjectController::targetTheta = 0.0;
double EjectController::distanceThreshold = 0.0;
double EjectController::angleThreshold = 0.0;

EjectController::EjectController() {
	hasCoordinates = false;
	hasAngle = false;
}

EjectController& EjectController::withCoordinates(double targetX, double targetY, double distanceThreshold) {
	this->targetX = targetX;
	this->targetY = targetY;
	this->distanceThreshold = distanceThreshold;
	hasCoordinates = true;
	return *this;
}

EjectController& EjectController::withAngle(double targetTheta, double angleThreshold) {
	this->targetTheta = targetTheta;
	this->angleThreshold = angleThreshold;
	hasAngle = true;
	return *this;
}

/**
 * Ejects one ball
*/
void EjectController::startEjecting(void* ignore)
{
	if (hasCoordinates) {
		double distanceError = distanceFormula(PositionController().getPosition(), { targetX, targetY });
		while (distanceError > distanceThreshold) {
			distanceError = distanceFormula(PositionController().getPosition(), { targetX, targetY });
			pros::delay(10);
		}
	}

	if (hasAngle) {
		double angleError = abs(calcAngleDiff(PositionController().getTheta(), targetTheta));
		while (angleError > angleThreshold) {
			angleError = abs(calcAngleDiff(PositionController().getTheta(), targetTheta));
			pros::delay(10);
		}
	}

	ejectingStatus = true;

	//Disables automated control of top and bottom rollers
	IndexController().toggleIndexing(false);

	// Reverse upper stack to allow upper ball to be ejected
	while (ejectingStatus) {
		upperStack = -127;
		lowerStack = -127;
	}

	//Resumes automated indexing
	IndexController().toggleIndexing(true);

	upperStack.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void EjectController::stopEjecting() {
	ejectingStatus = false;
}