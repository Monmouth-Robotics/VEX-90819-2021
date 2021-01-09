#include "macros/ejectController.h"

bool EjectController::ejectingStatus = false;
bool EjectController::useTopRoller = false;

EjectController::EjectController() {

}

EjectController& EjectController::setTopRoller(bool useTopRoller) {
	this->useTopRoller = useTopRoller;
	return *this;
}

/**
 * Ejects one ball
*/
void EjectController::ejectOneBall(void* ignore)
{
	ejectingStatus = false;

	if (useTopRoller)
	{
		//Disables automated control of top and bottom rollers
		indexer.toggleTop(true);
		indexer.toggleBottom(true);

		// Reverse upper stack to allow upper ball to be ejected
		while (indexer.getTopStatus() != "") {
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
		indexer.toggleBottom(true);
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
	indexer.toggleTopPosition(false);

	//Resumes automated control of top and bottom rollers
	indexer.toggleTop(false);
	indexer.toggleBottom(false);

	upperStack.set_brake_mode(MOTOR_BRAKE_HOLD);
	ejectingStatus = true;
}

/**
 * Ejects two balls
*/
void EjectController::ejectTwoBalls(void* ignore)
{
	ejectingStatus = false;

	if (useTopRoller)
	{
		//Disables automated control of top and bottom rollers
		indexer.toggleTop(true);
		indexer.toggleBottom(true);

		// Reverse upper stack to allow upper ball to be ejected
		while (indexer.getTopStatus() != "") {
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
		indexer.toggleBottom(true);

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
	indexer.toggleTopPosition(false);

	//Resumes automated control of top and bottom rollers
	indexer.toggleTop(false);
	indexer.toggleBottom(false);

	upperStack.set_brake_mode(MOTOR_BRAKE_HOLD);

	ejectingStatus = true;
}