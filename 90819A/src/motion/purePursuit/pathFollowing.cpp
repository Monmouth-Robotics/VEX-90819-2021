#include "motion/purePursuit/pathFollowing.h"

/*
Creates function that takes in current x, y, and theta and lookahead point x, y, theta, and returns proper error.
Function rotates the lookahead position about the robot origin.
*/

vector<double> getErrors(vector<double> currentPosition, vector<double> lookAheadPosition)
{
	vector<double> adjustedError;

	//calculates new x coordinate
	double rotatedX = cos(currentPosition[2]) * (lookAheadPosition[0] - currentPosition[0]) - sin(currentPosition[2]) * (lookAheadPosition[1] - currentPosition[1]) + currentPosition[0];
	//calculates new y coordinate
	double rotatedY = sin(currentPosition[2]) * (lookAheadPosition[0] - currentPosition[0]) + cos(currentPosition[2]) * (lookAheadPosition[1] - currentPosition[1]) + currentPosition[1];

	//calculates x error
	double xError = rotatedX - currentPosition[0];
	//calculates y error
	double yError = rotatedY - currentPosition[0];
	//calculates angle error
	double angleError = calcAngleDiff(currentPosition[2], lookAheadPosition[2]);

	//creates error vector
	adjustedError[0] = xError;
	adjustedError[1] = yError;
	adjustedError[2] = angleError;

	return adjustedError;
}

double findPercentage(double xError, double yError)
{
	if (abs(xError) < abs(yError))
	{
		return (1 - abs(xError / yError));
	}
	else
	{
		return (1 - abs(yError / xError));
	}
}

double signum(double number)
{
	if (number > 0)
	{
		return 1.0;
	}
	else if (number < 0)
	{
		return -1.0;
	}
	else
	{
		return 0.0;
	}
}
void moveRobot(vector<double> errors, double distanceError, double kPDistance, double kPTheta)
{
	double maxPower = kPDistance * distanceError; //127

	if (maxPower > 127){
		maxPower = 127;
	}
	else if (maxPower < -127){
		maxPower = -127;
	}
	double xError = errors[0];
	double yError = errors[1];
	double thetaError = errors[2];

	double leftFrontPower;
	double leftBackPower;
	double rightFrontPower;
	double rightBackPower;
	
	if (signum(xError) == signum(yError))
	{
		leftFrontPower = maxPower*signum(xError);
		rightBackPower = maxPower*signum(xError);
		if (xError > yError)
		{
			leftBackPower = -1 * maxPower * findPercentage(xError, yError);
			rightFrontPower = -1 * maxPower * findPercentage(xError, yError);
		}
		else
		{
			leftBackPower = maxPower * findPercentage(xError, yError);
			rightFrontPower = maxPower * findPercentage(xError, yError);
		}
	}
	else
	{
		leftBackPower = maxPower * signum(yError);
		rightFrontPower = maxPower * signum(yError);

		if (abs(xError)>abs(yError))
		{
			leftFrontPower = signum(xError) * maxPower * findPercentage(xError, yError);
			rightBackPower = signum(xError) * maxPower * findPercentage(xError, yError);
		}
		else
		{
			leftFrontPower = signum(yError) * maxPower * findPercentage(xError, yError);
			rightBackPower = signum(yError) * maxPower * findPercentage(xError, yError);
		}
	}

	printf("Motor speeds: %.3f, %.3f, %.3f, %.3f\n", leftFrontPower, rightBackPower, rightFrontPower, leftBackPower);
}