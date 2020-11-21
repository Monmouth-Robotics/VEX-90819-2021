#include "macros/indexing.h"

string topBallDetected = "";
string bottomBallDetected = "";
string backBallDetected = "";
string intakeBallColor = "";

bool topDisabled = false;
bool bottomDisabled = false;

string Indexing::getTopStatus()
{
	return topBallDetected;
}

string Indexing::getBottomStatus()
{
	return bottomBallDetected;
}

string Indexing::getBackStatus()
{
	return backBallDetected;
}

string Indexing::getIntakeColor()
{
	return intakeBallColor;
}

void Indexing::toggleTop(bool disabled)
{
	topDisabled = disabled;
}

void Indexing::toggleBottom(bool disabled)
{
	bottomDisabled = disabled;
}

void Indexing::indexingTask(void *ignore)
{
	while (true)
	{
		//is top ball there
		if (ultrasonicTopOne.get_value() < 80 || ultrasonicTopTwo.get_value() < 80)
		{
			topBallDetected = "red";
		}
		else
		{
			topBallDetected = "";
		}

		//if bottom ball there
		if (ultrasonicBottomOne.get_value() < 80 || ultrasonicBottomTwo.get_value() < 80)
		{
			bottomBallDetected = "red";
		}
		else
		{
			bottomBallDetected = "";
		}

		//if back ball there
		if (ultrasonicBack.get_value() < 80)
		{
			backBallDetected = "red";
		}
		else
		{
			backBallDetected = "";
		}

		//intake ball color
		if (opticalSensor.get_hue()<30){
			intakeBallColor = "red";
		}
		else if (opticalSensor.get_hue() > 1000){
			intakeBallColor = "blue";
		}
		else{
			intakeBallColor = "";
		}

		//motor control
		if (topBallDetected != "")
		{
			if (!topDisabled)
			{
				upperStack = 0;
			}
			if (!bottomDisabled)
			{
				lowerStack = 80;
			}
			if (bottomBallDetected != "")
			{
				if (!bottomDisabled)
				{
					lowerStack = 0;
				}
			}
		}
		else
		{
			lowerStack = 127;
			upperStack = 100;
		}
	}
	// while (true)
	// {
	// 	if (ultrasonicTop.get_value()<80 || ultrasonicBottom.get_value()<80)
	// 	{
	// 		upperStack = 0;
	// 		lowerStack = 63;
	// 		// printf("%lf", opticalSensor.get_hue());
	// 		topBallDetected = true;
	// 		// printf(opticalSensor.get_hue();)
	// 		if(opticalSensor.get_hue()<30||opticalSensor.get_hue()>1000)
	// 		{
	// 			lowerStack = 0;
	// 			bottomBallDetected = true;
	// 		}
	// 	}
	// 	else {
	// 		topBallDetected = false;
	// 		bottomBallDetected = false;
	// 		upperStack = 100;
	// 		lowerStack = 80;
	// 	}
	// 	pros::delay(10);
	// }
}