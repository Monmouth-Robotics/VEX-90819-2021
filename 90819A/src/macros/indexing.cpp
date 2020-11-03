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

void Indexing::initIndexing(void *ignore)
{
	while (true)
	{
		baseReadingTop = lineSensorTop.get_value();
		baseReadingBottom = lineSensorBottom.get_value();
		if (baseReadingTop > 0 && baseReadingBottom > 0)
		{
			printf("Base Readings Made");
			break;
		}
		pros::delay(10);
	}
}

void Indexing::indexingTask(void *ignore)
{
	while (true)
	{
		if (baseReadingTop > 0 && baseReadingBottom > 0)
		{
			if (abs(lineSensorTop.get_value() - baseReadingTop) > 5)
			{
				printf("Top Ball Detected");
				if (!topBallDetected)
				{
					topBallDetected = true;
					upperStack = -63;
					pros::delay(10);
					upperStack = 0;
				}
				if (abs(lineSensorBottom.get_value() - baseReadingBottom) > 10)
				{
					printf("Lower Ball Detected");
					lowerStack = 0;
					bottomBallDetected = true;
				}
			}
			else
			{
				lowerStack = 127;
				upperStack = 127;
				topBallDetected = false;
				bottomBallDetected = false;
			}

			pros::delay(10);
		}
	}
}