#include "macros/macroFunctions.h"

void MacroFunctions::shootOneBall(void *ignore)
{
	if (indexer.getTopStatus())
	{
		indexController.suspend();
		while (ultrasonicTop.get_value()<80 || ultrasonicBottom.get_value()<80)
		{
			upperStack = 127;
			lowerStack = 70;
		}
		indexController.resume();
	}
}

void MacroFunctions::shootOneBall()
{	
	while (!indexer.getTopStatus())
	{
		pros::delay(10);
	}
	
	if (indexer.getTopStatus())
	{	
		indexController.suspend();
		lowerStack = 0;
		while (ultrasonicTop.get_value()<80 || ultrasonicBottom.get_value()<80)
		{
			upperStack = 127;
			pros::delay(10);
			// lowerStack = 127;
		}
		indexController.resume();
	}
}

void MacroFunctions::shootTwoBalls(void *ignore)
{
	// if (indexer.getTopStatus() && indexer.getBottomStatus())
	// {
	// 	indexController.suspend();

	// 	upperStack = 127;
	// 	pros::delay(0);
	// 	lowerStack = 127;

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
