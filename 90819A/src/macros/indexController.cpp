#include "macros/indexController.h"

char* IndexController::topBallColor = "";
char* IndexController::intakeBallColor = "";

bool IndexController::indexDisabled = false;

/**
 * Returns status of top indexing position
*/
char* IndexController::getTopColor()
{
	return topBallColor;
}

/**
 * Returns status of ball in intakes
*/
char* IndexController::getIntakeColor()
{
	return intakeBallColor;
}

/**
 * Toggles automatic control of indexing
*/
void IndexController::toggleIndexing(bool enabled)
{
	indexDisabled = !enabled;
}

/**
 * Automates indexing of balls in robot
*/
void IndexController::indexingTask(void* ignore)
{
	//Turn on LED for optical sensor
	opticalSensorTop.set_led_pwm(100);
	opticalSensorIntake.set_led_pwm(100);

	while (true)
	{
		//Determines status of ball in intakes
		if (opticalSensorTop.get_hue() < 30)
		{
			topBallColor = "red";
		}
		else if (opticalSensorTop.get_hue() > 150)
		{
			topBallColor = "blue";
		}
		else
		{
			topBallColor = "";
		}

		//Determines status of ball in intakes
		if (opticalSensorIntake.get_hue() < 30)
		{
			intakeBallColor = "red";
		}
		else if (opticalSensorIntake.get_hue() > 150)
		{
			intakeBallColor = "blue";
		}
		else
		{
			intakeBallColor = "";
		}

		if (!indexDisabled)
		{
			if (topBallColor == "")
			{
				upperStack = 127;
				lowerStack = 127;
			}
			else
			{
				upperStack = 0;
				lowerStack = 0;
			}
		}

		pros::delay(10);
	}
}