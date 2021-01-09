#include "init/utility.h"


/**
 * Calculates signed difference between two headings
 */
double calcAngleDiff(double angle1, double angle2)
{
	double num1 = angle1 - angle2;
	double num2 = (angle1 - 2 * M_PI) - angle2;
	double num3 = angle1 - (angle2 - 2 * M_PI);
	if (abs(num1) < abs(num2) && abs(num1) < abs(num3))
	{
		return num1;
	}
	else if (abs(num2) < abs(num1) && abs(num2) < abs(num3))
	{
		return num2;
	}
	else
	{
		return num3;
	}
}

/**
 * Uses distance formula to calculate distance error between two positions
 */
double distanceFormula(vector<double> currentPosition, vector<double> lookAheadPosition) {
	double xError = lookAheadPosition[0] - currentPosition[0];
	double yError = lookAheadPosition[1] - currentPosition[1];

	double distanceError = sqrt(pow(xError, 2) + pow(yError, 2));

	return distanceError;
}

/**
 * Calculates the average heading for two inertial sensors
 */
double averageHeadings(double angle1, double angle2)
{
	double diff1, diff2;
	if (angle1 > M_PI)
	{
		diff1 = angle1 - 2 * M_PI;
	}
	else
	{
		diff1 = angle1;
	}

	if (angle2 > M_PI)
	{
		diff2 = angle2 - 2 * M_PI;
	}
	else
	{
		diff2 = angle2;
	}

	double avgAngle = (diff1 + diff2) / 2;

	if (avgAngle < 0)
	{
		return 2 * M_PI + avgAngle;
	}
	else
	{
		return avgAngle;
	}
}

/**
 * Calculates the average heading for three inertial sensors
 */
double averageHeadings(double angle1, double angle2, double angle3)
{
	double diff1, diff2, diff3;
	if (angle1 > M_PI)
	{
		diff1 = angle1 - 2 * M_PI;
	}
	else
	{
		diff1 = angle1;
	}

	if (angle2 > M_PI)
	{
		diff2 = angle2 - 2 * M_PI;
	}
	else
	{
		diff2 = angle2;
	}

	if (angle3 > M_PI)
	{
		diff3 = angle3 - 2 * M_PI;
	}
	else
	{
		diff3 = angle3;
	}

	double avgAngle = (diff1 + diff2 + diff3) / 3;

	if (avgAngle < 0)
	{
		return 2 * M_PI + avgAngle;
	}
	else
	{
		return avgAngle;
	}
}

/**
 * Calculates signed difference between three angles
 */
double headingAverageBeta(double angle1, double angle2, double angle3)
{
	double oneTwo = calcAngleDiff(angle1, angle2);
	double twoThree = calcAngleDiff(angle2, angle3);
	double oneThree = calcAngleDiff(angle1, angle3);

	if (abs(oneTwo) < abs(twoThree) && abs(oneTwo) < abs(oneThree))
	{
		return angle1 + calcAngleDiff(angle2, angle1) / 2;

	}
	else if (abs(twoThree) < abs(oneTwo) && abs(twoThree) < abs(oneThree))
	{
		return angle2 + calcAngleDiff(angle3, angle2) / 2;
	}
	else
	{
		return angle3 + calcAngleDiff(angle1, angle3) / 2;
	}

}

/**
 * Calculates dot product of two vectors
 */
double dot(vector<double> a, vector<double> b)
{
	return a[0] * b[0] + a[1] * b[1];
}

/**
 * Converts value from m/s to rpm
 */
double convertToRPM(double value, double wheelDiameter)
{
	return value / (2 * M_PI * wheelDiameter * 2.54) * (100 * 2 * 60.0);
}

/**
 * Converts value from m/s to rpm
 */
double convertToRPM(int value, double wheelDiameter)
{
	return value / (2 * M_PI * wheelDiameter * 2.54) * (100 * 2 * 60.0);
}

/**
 * Converts value from rpm to m/s
 */
double convertToMeters(double value, double wheelDiameter)
{
	return value * (2 * M_PI * wheelDiameter * 2.54) / (100 * 2 * 60.0);
}

/**
 * Converts value from rpm to m/s
 */
double convertToMeters(int value, double wheelDiameter)
{

	return value * (2 * M_PI * wheelDiameter * 2.54) / (100 * 2 * 60.0);
}

/**
 * Returns sign of integer value
 */
int signum(int value) {
	return (value > 0) - (value < 0);
}

/**
 * Returns sign of double value
 */
int signum(double value) {
	return (value > 0) - (value < 0);
}

double restrictAngle(double theta) {
	while (theta > M_PI * 2)
	{
		theta -= M_PI * 2;
	}
	while (theta < 0)
	{
		theta += M_PI * 2;
	}
	return theta;
}