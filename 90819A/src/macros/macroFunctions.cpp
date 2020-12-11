#include "macros/macroFunctions.h"

bool poopingStatus = false;

/**
 * Shoots two balls
*/
void MacroFunctions::shootTwoBalls(void* ignore)
{
	//Disables automated control of top and bottom rollers
	indexer.toggleTop(true);
	indexer.toggleBottom(true);
	lowerStack = 0;
	upperStack = 127;

	//Waits for ball to be located in top indexing position
	while (limitSwitchTop.get_value() == 0){
		pros::delay(10);
	}
	
	//Shoots until ball leaves top indexing position
	while (limitSwitchTop.get_value() == 1)
	{	
		pros::delay(10);
	}

	pros::delay(250);

	lowerStack = 127;
	upperStack = 127;

	//Waits for ball to be located in top indexing position
	while (limitSwitchTop.get_value() == 0)
	{
		pros::delay(10);
	}

	lowerStack = 0;

	//Shoots until ball leaves top indexing position
	while (limitSwitchTop.get_value()==1)
	{
		pros::delay(10);
	}

	upperStack = 0;

	//Resumes automated control of top and bottom rollers
	indexer.toggleTop(false);
	indexer.toggleBottom(false);
}

/**
 * Shoots one ball
*/
void MacroFunctions::shootOneBall(void* ignore)
{
	//Disables automated control of top roller
	indexer.toggleTop(true);
	upperStack = 127;

	//Waits for ball to be located in top indexing position
	while (indexer.getTopStatus() == "")
	{
		pros::delay(10);
	}

	//Shoots until ball leaves top indexing position
	if (indexer.getTopStatus() != "")
	{
		while (indexer.getTopStatus() != "")
		{
			pros::delay(10);
		}
	}

	//Resumes automated control of top roller
	indexer.toggleTop(false);
}

/**
 * Ejects one ball
*/
void MacroFunctions::poopOneBall(void* param)
{
	poopingStatus = false;
	bool useTopRoller = (bool)param;

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
	poopingStatus = true;
}

/**
 * Ejects two balls
*/
void MacroFunctions::poopTwoBalls(void* param)
{
	poopingStatus = false;
	bool useTopRoller = (bool)param;

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

	poopingStatus = true;
}

/**
 * Toggles intakes to given speed
*/
void MacroFunctions::toggleIntakes(int speed)

{
	intakeMotorLeft = speed;
	intakeMotorRight = speed;
	
}

void MacroFunctions::deploy(void* ignore){
	indexer.toggleTop(true);
	indexer.toggleBottom(true);
	lowerStack = -63;
	upperStack = -80;
	pros::delay(500);
	// upperStack = -80;
	// lowerStack = 0;
	// pros::delay(1000);
	indexer.toggleTop(false);
	indexer.toggleBottom(false);
	toggleIntakes(127);
	pros::delay(500);
	

}