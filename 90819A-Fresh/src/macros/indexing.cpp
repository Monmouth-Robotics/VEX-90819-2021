#include "macros/indexing.h"

int baseReadingTop = 0;
int baseReadingBottom = 0;
bool topBallDetected = false;
bool bottomBallDetected = true;

bool Indexing::getTopStatus()
{
	return topBallDetected;
}

bool Indexing::getBottomStatus()
{
	return bottomBallDetected;
}

void Indexing::setBottomStatus(bool status)
{
	bottomBallDetected = status;
}

void Indexing::setTopStatus(bool status)
{
	topBallDetected = status;
}

int Indexing::getBaseTop()
{
	return baseReadingTop;
}

int Indexing::getBaseBottom()
{
	return baseReadingBottom;
}

void Indexing::indexingTask(void *ignore)
{
	while (true)
	{
		if (ultrasonicTop.get_value()<80 || ultrasonicBottom.get_value()<80)
		{
			upperStack = 0;
			lowerStack = 63;
			// printf("%lf", opticalSensor.get_hue());
			topBallDetected = true;
			// printf(opticalSensor.get_hue();)
			if(opticalSensor.get_hue()<30||opticalSensor.get_hue()>1000)
			{
				lowerStack = 0;
				bottomBallDetected = true;
			}
		}
		else {
			topBallDetected = false;
			bottomBallDetected = false;
			upperStack = 100;
			lowerStack = 80;
		}
		pros::delay(10);
	}
}