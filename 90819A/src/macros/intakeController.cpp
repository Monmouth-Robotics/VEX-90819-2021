#include "macros/intakeController.h"

namespace zoo {
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
}