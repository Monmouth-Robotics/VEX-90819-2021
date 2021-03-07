#include "macros/shootController.h"

ShootController::ShootController() {

}

/**
 * Shoots balls continuously
*/
void ShootController::shoot(void* ignore)
{	
	//Disables automated control of indexing
	IndexController().toggleIndexing(false);
	
	
	upperStack = 127;
	lowerStack = 127;

	//Waits for ball to be located in top indexing position
	while (IndexController().getTopColor() != "blue")
	{
		pros::delay(10);
	}

	//Resumes automated control of top roller
	IndexController().toggleTop(false);
}