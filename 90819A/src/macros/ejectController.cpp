#include "macros/ejectController.h"

bool EjectController::ejectingStatus = false;
bool EjectController::useTopRoller = false;
bool EjectController::hasCoordinates = false;
bool EjectController::hasAngle = false;
double EjectController::targetX = 0.0;
double EjectController::targetY = 0.0;
double EjectController::targetTheta = 0.0;
double EjectController::distanceThreshold = 0.0;
double EjectController::angleThreshold = 0.0;

EjectController::EjectController() {
	useTopRoller = false;
	hasCoordinates = false;
	hasAngle = false;
}

EjectController& EjectController::setTopRoller(bool useTopRoller) {
	this->useTopRoller = useTopRoller;
	return *this;
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
void EjectController::ejectOneBall(void* ignore)
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

	ejectingStatus = false;

	if (useTopRoller)
	{
		//Disables automated control of top and bottom rollers
		IndexController().toggleTop(true);
		IndexController().toggleBottom(true);

		// Reverse upper stack to allow upper ball to be ejected
		while (IndexController().getTopStatus() != "") {
			upperStack = -127;
			lowerStack = -127;
		}


		//Waits until ball is ejected
		while (limitSwitch.get_value() != 1)
		{
			printf("limit: %d\n", limitSwitch.get_value());
			upperStack = -127;
			lowerStack = 127;
			pros::delay(10);
		}

		//Waits while limit switch is still triggered
		while (limitSwitch.get_value() == 1)
		{
			pros::delay(10);
		}
	}

	else
	{
		//Disables automated control of bottom roller
		IndexController().toggleBottom(true);
		upperStack.set_brake_mode(MOTOR_BRAKE_BRAKE);

		//Waits until ball is ejected
		while (limitSwitch.get_value() != 1)
		{
			printf("limit: %d\n", limitSwitch.get_value());
			lowerStack = 127;
			pros::delay(10);
		}

		//Waits while limit switch is still triggered
		while (limitSwitch.get_value() == 1)
		{
			pros::delay(10);
		}
	}

	//Enables use of top indexing position
	IndexController().toggleTopPosition(false);

	//Resumes automated control of top and bottom rollers
	IndexController().toggleTop(false);
	IndexController().toggleBottom(false);

	upperStack.set_brake_mode(MOTOR_BRAKE_HOLD);
	ejectingStatus = true;
}

/**
 * Ejects two balls
*/
void EjectController::ejectTwoBalls(void* ignore)
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

	ejectingStatus = false;

	if (useTopRoller)
	{
		//Disables automated control of top and bottom rollers
		IndexController().toggleTop(true);
		IndexController().toggleBottom(true);

		// Reverse upper stack to allow upper ball to be ejected
		while (IndexController().getTopStatus() != "") {
			upperStack = -127;
			lowerStack = -127;
		}

		//Waits until ball is ejected
		while (limitSwitch.get_value() != 1)
		{
			printf("limit: %d\n", limitSwitch.get_value());
			upperStack = -127;
			lowerStack = 127;
			pros::delay(10);
		}

		//Waits while limit switch is still triggered
		while (limitSwitch.get_value() == 1)
		{
			pros::delay(10);
		}

		lowerStack = 0;
		upperStack = 0;
		pros::delay(500);

		//Waits until ball is ejected
		while (limitSwitch.get_value() != 1)
		{
			printf("limit: %d\n", limitSwitch.get_value());
			upperStack = -127;
			lowerStack = 127;
			pros::delay(10);
		}

		//Waits while limit switch is still triggered
		while (limitSwitch.get_value() == 1)
		{
			pros::delay(10);
		}
	}
	else
	{
		//Disables automated control of bottom roller
		IndexController().toggleBottom(true);

		upperStack.set_brake_mode(MOTOR_BRAKE_COAST);

		//Waits until ball is ejected
		while (limitSwitch.get_value() != 1)
		{
			printf("limit: %d\n", limitSwitch.get_value());
			lowerStack = 127;
			pros::delay(10);
		}

		//Waits while limit switch is still triggered
		while (limitSwitch.get_value() == 1)
		{
			pros::delay(10);
		}

		pros::delay(100);

		//Waits until ball is ejected
		while (limitSwitch.get_value() != 1)
		{
			printf("limit: %d\n", limitSwitch.get_value());
			lowerStack = 127;
			pros::delay(10);
		}

		//Waits while limit switch is still triggered
		while (limitSwitch.get_value() == 1)
		{
			pros::delay(10);
		}
	}


	//Enables use of top indexing position
	IndexController().toggleTopPosition(false);

	//Resumes automated control of top and bottom rollers
	IndexController().toggleTop(false);
	IndexController().toggleBottom(false);

	upperStack.set_brake_mode(MOTOR_BRAKE_HOLD);

	ejectingStatus = true;
}