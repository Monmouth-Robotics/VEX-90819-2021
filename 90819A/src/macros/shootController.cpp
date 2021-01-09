#include "macros/shootController.h"

namespace zoo {

	ShootController::ShootController() {

	}

	/**
	 * Shoots two balls
	*/
	void ShootController::shootPowerful(void* ignore)
	{
		//disables automated control of top and bottom roller
		indexer.toggleTop(true);
		indexer.toggleBottom(true);

		upperStack = -127;
		lowerStack = -63;
		// lowerStack = -127;

		pros::delay(250);

		indexer.toggleTop(false);
		indexer.toggleBottom(false);

		// upperStack = 127;
		// lowerStack = 127;

		shootOneBall(NULL);
	}

	void ShootController::shootTwoBalls(void* ignore)
	{
		//Disables automated control of top and bottom rollers
		indexer.toggleTop(true);
		indexer.toggleBottom(true);
		lowerStack = 0;
		upperStack = 127;

		//Waits for ball to be located in top indexing position
		while (limitSwitchTop.get_value() == 0) {
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
		while (limitSwitchTop.get_value() == 1)
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
	void ShootController::shootOneBall(void* ignore)
	{
		//Disables automated control of top roller
		indexer.toggleTop(true);
		upperStack = 127;

		//Waits for ball to be located in top indexing position
		while (limitSwitchTop.get_value() == 0)
		{
			pros::delay(10);
		}

		//Shoots until ball leaves top indexing position
		while (limitSwitchTop.get_value() == 1)
		{
			pros::delay(10);
		}

		//Resumes automated control of top roller
		indexer.toggleTop(false);
	}
}
