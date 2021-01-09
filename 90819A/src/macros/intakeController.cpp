#include "macros/intakeController.h"

namespace zoo {
	bool IntakeController::intakeStatus = false;

	IntakeController::IntakeController() {

	}

	/**
	 * Toggles intakes to given speed
	*/
	void IntakeController::toggleIntakes(int speed)

	{
		intakeMotorLeft = speed;
		intakeMotorRight = speed;

	}

	void IntakeController::deploy(void* ignore) {
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
		IntakeController().toggleIntakes(127);
		pros::delay(500);
	}

	/**
 * Stops intakes when two blue balls need to be descored
*/
	void IntakeController::stopIntakesAsync(void* ignore)
	{
		intakeStatus = false;

		while (indexer.getIntakeColor() != "blue")
		{
			pros::delay(10);
		}

		//Waits for intakes to contain red ball
		while (indexer.getIntakeColor() != "red")
		{
			pros::delay(10);
		}

		intakeStatus = true;

		//Outtakes until intakes no longer contain red ball
		while (indexer.getIntakeColor() == "red")
		{
			IntakeController().toggleIntakes(-127);
		}

		// indexerFunctions.toggleIntakes(0);

		// pros::delay(500);

		IntakeController().toggleIntakes(0);
	}

	/**
	 * Stops intakes when one blue ball needs to be descored
	*/
	void IntakeController::stopIntakesAsyncOne(void* ignore)
	{
		intakeStatus = false;

		//Waits for intakes to contain one blue ball
		while (indexer.getIntakeColor() != "blue")
		{
			pros::delay(10);
		}
		IntakeController().toggleIntakes(0);
		intakeStatus = true;
	}

	bool IntakeController::getIntakeStatus() {
		return intakeStatus;
	}
}