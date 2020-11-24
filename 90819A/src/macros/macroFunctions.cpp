#include "macros/macroFunctions.h"

bool poopingStatus = false;

void MacroFunctions::shootOneBallAsync(void *ignore)
{
	indexer.toggleTop(true);
	upperStack = 127;
	if (indexer.getTopStatus() != "")
	{
		while (indexer.getTopStatus() != "")
		{
			pros::delay(10);
		}
	}
	indexer.toggleTop(false);
}

void MacroFunctions::shootOneBall()
{
	indexer.toggleTop(true);
	upperStack = 127;

	while (indexer.getTopStatus() == "")
	{
		pros::delay(10);
	}

	if (indexer.getTopStatus() != "")
	{
		while (indexer.getTopStatus() != "")
		{
			pros::delay(10);
		}
	}

	indexer.toggleTop(false);
}

void MacroFunctions::poopOneBall(void *ignore)
{	
	poopingStatus = false;

	indexer.toggleTop(true);
	indexer.toggleBottom(true);

	while (limitSwitch.get_value() != 1){
		printf("limit: %d\n", limitSwitch.get_value());
		upperStack = -60;
		lowerStack = 60;
		pros::delay(10);
	}

	while (limitSwitch.get_value() == 1){
		pros::delay(10);
	}

	// while(indexer.getBottomStatus() == ""){
	// 	pros::delay(10);
	// }

	// while (indexer.getBottomStatus() != "")
	// {
	// 	// upperStack = -127;
	// 	upperStack = -55;
	// 	lowerStack = 55;
	// 	pros::delay(10);
	// 	printf("first\n");
	// }

	// upperStack = -63;
	// lowerStack = 63;
	// pros::delay(1250);

	indexer.toggleTop(false);
	indexer.toggleBottom(false);

	poopingStatus = true;
}

void MacroFunctions::poopTwoBalls(void *ignore)
{
	poopingStatus = false;

	indexer.toggleTop(true);
	indexer.toggleBottom(true);

	while (limitSwitch.get_value() != 1){
		printf("limit: %d\n", limitSwitch.get_value());
		upperStack = -80;
		lowerStack = 80;
		pros::delay(10);
	}

	while (limitSwitch.get_value() == 1){
		pros::delay(10);
	}

	// while(indexer.getBottomStatus() == ""){
	// 	pros::delay(10);
	// }

	// while (indexer.getBottomStatus() != "")
	// {
	// 	// upperStack = -127;
	// 	upperStack = -55;
	// 	lowerStack = 55;
	// 	pros::delay(10);
	// 	printf("first\n");
	// }

	// upperStack = -63;
	// lowerStack = 63;
	// pros::delay(1250);

	indexer.toggleTop(false);
	indexer.toggleBottom(false);

	poopingStatus = true;

	pros::delay(500);

	poopingStatus = false;

	indexer.toggleTop(true);
	indexer.toggleBottom(true);

	while (limitSwitch.get_value() != 1){
		printf("limit: %d\n", limitSwitch.get_value());
		upperStack = -127;
		lowerStack = 127;
		pros::delay(10);
	}

	while (limitSwitch.get_value() == 1){
		pros::delay(10);
	}

	// while(indexer.getBottomStatus() == ""){
	// 	pros::delay(10);
	// }

	// while (indexer.getBottomStatus() != "")
	// {
	// 	// upperStack = -127;
	// 	upperStack = -55;
	// 	lowerStack = 55;
	// 	pros::delay(10);
	// 	printf("first\n");
	// }

	// upperStack = -63;
	// lowerStack = 63;
	// pros::delay(1250);

	indexer.toggleTop(false);
	indexer.toggleBottom(false);

	poopingStatus = true;
}

void MacroFunctions::shootTwoBallsAsync(void *ignore)
{
	indexer.toggleTop(true);
	indexer.toggleBottom(true);
	lowerStack = 0;
	upperStack = 127;

	while (indexer.getTopStatus() != "")
	{
		pros::delay(10);
	}

	lowerStack = 127;
	upperStack = 127;

	while (indexer.getTopStatus() == "")
	{
		pros::delay(10);
	}

	lowerStack = 0;

	while (indexer.getTopStatus() != "")
	{
		pros::delay(10);
	}

	upperStack = 0;

	indexer.toggleTop(false);
	indexer.toggleBottom(false);

	// 	//wait for bottom ball to leave
	// 	while (abs(lineSensorBottom.get_value() - indexer.getBaseBottom() > 5))
	// 	{
	// 		pros::delay(10);
	// 	}

	// 	//wait for top ball detection, start bottom ball indexing
	// 	while (abs(lineSensorTop.get_value() - indexer.getBaseTop()) < 5)
	// 	{
	// 		if (abs(lineSensorBottom.get_value() - indexer.getBaseBottom()) > 10)
	// 		{
	// 			printf("Lower Ball Detected");
	// 			lowerStack = 0;
	// 			indexer.setBottomStatus(true);
	// 		}
	// 		pros::delay(10);
	// 	}

	// 	//wait for top ball to leave, keep bottom ball indexing
	// 	while (abs(lineSensorTop.get_value() - indexer.getBaseTop()) > 5)
	// 	{
	// 		if (abs(lineSensorBottom.get_value() - indexer.getBaseBottom()) > 10)
	// 		{
	// 			printf("Lower Ball Detected");
	// 			lowerStack = 0;
	// 			indexer.setBottomStatus(true);
	// 		}
	// 		pros::delay(10);
	// 	}

	// 	//resume top ball indexing
	// 	indexController.resume();
	// }
}

void MacroFunctions::toggleIntakes(int speed)
{
	intakeMotorLeft = speed;
	intakeMotorRight = speed;
}