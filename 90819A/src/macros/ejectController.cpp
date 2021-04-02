#include "macros/ejectController.h"

bool EjectController::ejectingStatus = false;
bool EjectController::hasStartCoordinates = false;
bool EjectController::hasStartAngle = false;
bool EjectController::hasEndCoordinates = false;
bool EjectController::hasEndAngle = false;
double EjectController::targetStartX = 0.0;
double EjectController::targetStartY = 0.0;
double EjectController::targetStartTheta = 0.0;
double EjectController::targetEndX = 0.0;
double EjectController::targetEndY = 0.0;
double EjectController::targetEndTheta = 0.0;
double EjectController::distanceStartThreshold = 0.0;
double EjectController::angleStartThreshold = 0.0;
double EjectController::distanceEndThreshold = 0.0;
double EjectController::angleEndThreshold = 0.0;

EjectController::EjectController() {
	hasStartCoordinates = false;
	hasStartAngle = false;
	hasEndCoordinates = false;
	hasEndAngle = false;
}

EjectController& EjectController::withStartCoordinates(double targetStartX, double targetStartY, double distanceStartThreshold) {
	this->targetStartX = targetStartX;
	this->targetStartY = targetStartY;
	this->distanceStartThreshold = distanceStartThreshold;
	hasStartCoordinates = true;
	return *this;
}

EjectController& EjectController::withStartAngle(double targetStartTheta, double angleStartThreshold) {
	this->targetStartTheta = targetStartTheta;
	this->angleStartThreshold = angleStartThreshold;
	hasStartAngle = true;
	return *this;
}

EjectController& EjectController::withEndCoordinates(double targetEndX, double targetEndY, double distanceEndThreshold) {
	this->targetEndX = targetEndX;
	this->targetEndY = targetEndY;
	this->distanceEndThreshold = distanceEndThreshold;
	hasEndCoordinates = true;
	return *this;
}

EjectController& EjectController::withEndAngle(double targetEndTheta, double angleEndThreshold) {
	this->targetEndTheta = targetEndTheta;
	this->angleEndThreshold = angleEndThreshold;
	hasEndAngle = true;
	return *this;
}

/**
 * Ejects one ball
*/
void EjectController::eject(void* ignore)
{
	if (hasStartCoordinates) {
		double distanceError = distanceFormula(PositionController().getPosition(), { targetStartX, targetStartY });
		while (distanceError > distanceStartThreshold) {
			distanceError = distanceFormula(PositionController().getPosition(), { targetStartX, targetStartY });
			pros::delay(10);
		}
	}

	if (hasStartAngle) {
		double angleError = abs(calcAngleDiff(PositionController().getTheta(), targetStartTheta));
		while (angleError > angleStartThreshold) {
			angleError = abs(calcAngleDiff(PositionController().getTheta(), targetStartTheta));
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

		if (hasEndAngle) {
			double angleError = abs(calcAngleDiff(PositionController().getTheta(), targetEndTheta));
			if (angleError < angleEndThreshold) {
				if (hasEndCoordinates) {
					double distanceError = distanceFormula(PositionController().getPosition(), { targetEndX, targetEndY });
					if (distanceError < distanceEndThreshold) {
						ejectingStatus = false;
					}
				}
				else {
					ejectingStatus = false;
				}
			}
		}
		else if (hasEndCoordinates) {
			double distanceError = distanceFormula(PositionController().getPosition(), { targetEndX, targetEndY });
			if (distanceError < distanceEndThreshold) {
				ejectingStatus = false;
			}
		}
	}

	IntakeController().toggleIntakes(-127);

	//Resumes automated indexing
	IndexController().toggleIndexing(true);
}

void EjectController::stopEjecting() {
	ejectingStatus = false;
}