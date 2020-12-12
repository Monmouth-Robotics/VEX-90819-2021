#include "macros/indexing.h"

char *topBallDetected = "";
char *bottomBallDetected = "";
char *backBallDetected = "";
char *intakeBallColor = "";

bool topDisabled = false;
bool topPositionDisabled = false;
bool bottomDisabled = false;

/**
 * Returns status of top indexing position
*/
char *Indexing::getTopStatus()
{
	return topBallDetected;
}

/**
 * Returns status of bottom indexing position
*/
char *Indexing::getBottomStatus()
{
	return bottomBallDetected;
}

/**
 * Returns status of ball in intakes
*/
char *Indexing::getIntakeColor()
{
	return intakeBallColor;
}

/**
 * Toggles usage of top indexing position
*/
void Indexing::toggleTopPosition(bool disabled)
{
	topPositionDisabled = disabled;
}

/**
 * Toggles automatic control of top indexing position
*/
void Indexing::toggleTop(bool disabled)
{
	topDisabled = disabled;
}

/**
 * Toggles automatic control of bottom indexing position
*/
void Indexing::toggleBottom(bool disabled)
{
	bottomDisabled = disabled;
}

/**
 * Automates indexing of balls in robot
*/
void Indexing::indexingTask(void *ignore)
{
	//Turn on LED for optical sensor
	opticalSensor.set_led_pwm(100);

	while (true)
	{
		//Determines status of top indexing position (not color sensitive)
		if (ultrasonicTopUpper.get_value() < 80 || ultrasonicTopLower.get_value() < 80)
		{
			topBallDetected = "red";
		}
		else
		{
			topBallDetected = "";
		}

		//Determines status of top bottom indexing position (not color sensitive)
		if (ultrasonicBottomUpper.get_value() < 80 || ultrasonicBottomLower.get_value() < 80)
		{
			bottomBallDetected = "red";
		}
		else
		{
			bottomBallDetected = "";
		}

		//Determines status of ball in intakes
		if (opticalSensor.get_hue() < 30)
		{
			intakeBallColor = "red";
		}
		else if (opticalSensor.get_hue() > 150)
		{
			intakeBallColor = "blue";
		}
		else
		{
			intakeBallColor = "";
		}

		if (topPositionDisabled)
		{
			if (topBallDetected != "")
			{
				upperStack = -127;
				lowerStack = -127;
			}
			else
			{
				if (bottomBallDetected != "")
				{
					if (!bottomDisabled)
					{
						lowerStack = 0;
						upperStack = 0;
					}
				}
				else
				{
					if (!bottomDisabled)
					{
						upperStack = 0;
						lowerStack = 63;
					}
				}
			}
		}
		else
		{
			if (topBallDetected != "")
			{
				if (!topDisabled)
				{
					//Spins top roller backwards if only the top upper ultrasonic is triggered
					if ((ultrasonicTopUpper.get_value() < 80 && ultrasonicTopLower.get_value() > 80) || limitSwitchTop.get_value() == 1)
					{
						upperStack = -63;
					}

					//Spins top roller forwards slowly if only the top lower ultrasonic is triggered
					else if (ultrasonicTopLower.get_value() < 80 && ultrasonicTopUpper.get_value() > 80)
					{
						upperStack = 10;
					}

					else
					{
						upperStack = 0;
					}
				}
				if (bottomBallDetected != "")
				{
					if (!bottomDisabled)
					{
						lowerStack = 0;
						//Spins bottom roller backwards if only the bottom upper ultrasonic is triggered
						// if (ultrasonicBottomUpper.get_value() < 80 && ultrasonicBottomLower.get_value() > 80)
						// {
						// 	lowerStack = -50;
						// }

						// //Spins bottom roller forwards slowly if only the bottom lower ultrasonic is triggered
						// else if (ultrasonicBottomLower.get_value() < 80 && ultrasonicBottomUpper.get_value() > 80)
						// {
						// 	lowerStack = 20;
						// }

						// else
						// {
						// 	lowerStack = 0;
						// }
					}
				}
				else
				{
					if (!bottomDisabled)
					{
						lowerStack = 63;
					}
				}
			}
			else
			{
				if (!bottomDisabled)
				{
					lowerStack = 127;
				}

				if (!topDisabled)
				{
					upperStack = 80;
				}
			}
		}

		pros::delay(10);
	}
}