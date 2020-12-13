#include "positioning/positionAlg.h"


double WHEEL_DIAMETER = 2.75;
double DISTANCE_TO_LEFT_ENCODER = 5.375;
double DISTANCE_TO_RIGHT_ENCODER = 5.375;
double DISTANCE_TO_BACK_ENCODER = 6.0625;

double previousLeftEncoderDegrees = 0;
double previousRightEncoderDegrees = 0;
double previousBackEncoderDegrees = 0;

double leftEncoderDegrees = 0;
double rightEncoderDegrees = 0;
double backEncoderDegrees = 0;

double leftEncoderDegreesDifference = 0;
double rightEncoderDegreesDifference = 0;
double backEncoderDegreesDifference = 0;

double leftEncoderRadians = 0;
double rightEncoderRadians = 0;
double backEncoderRadians = 0;

double leftEncoderDistance = 0;
double rightEncoderDistance = 0;
double backEncoderDistance = 0;

double deltaTheta = 0;
double polarTheta = 0;
double theta = 0;

vector<double> positionVector = {0, 0};
vector<double> newVector = {0, 0};

vector<double> testVector(1000, -1);
vector<double> leftVector(1000, 999999);
vector<double> rightVector(1000, 9999999);

double x;
double y;
double r;
double newX;
double newY;
double thetaM;

double inertLast = 0;
double inertLeft = 0;
double inertRight = 0;
double inertTheta = 0;
double inertCenter = 0;
int count2 = 0;

/**
 * Returns robot heading
 */
double PositionAlg::getTheta()
{
	return theta;
}

/**
 * Returns robot position
 */
vector<double> PositionAlg::getPosition()
{
	return positionVector;
}

/**
 * Calculates signed difference between two angles
 */

double PositionAlg::headingAverageBeta(double angle1, double angle2, double angle3)
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

double PositionAlg::calcAngleDiff(double angle1, double angle2)
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
 * Calculates robot position using odometry algorithm
 */
void PositionAlg::calcPosition(void *ignore)
{

	while (true)
	{
		//Gets raw values from encoders
		leftEncoderDegrees = leftEncoder.get_value();
		rightEncoderDegrees = rightEncoder.get_value();
		backEncoderDegrees = backEncoder.get_value();

		printf("Encoders: %.3f, %.3f, %.3f\n", leftEncoderDegrees, rightEncoderDegrees, backEncoderDegrees);

		//Finds the amount of degrees turned since last reading
		leftEncoderDegreesDifference = leftEncoderDegrees - previousLeftEncoderDegrees;
		rightEncoderDegreesDifference = rightEncoderDegrees - previousRightEncoderDegrees;
		backEncoderDegreesDifference = backEncoderDegrees - previousBackEncoderDegrees;

		//Sets last encoder measurement
		previousLeftEncoderDegrees = leftEncoderDegrees;
		previousRightEncoderDegrees = rightEncoderDegrees;
		previousBackEncoderDegrees = backEncoderDegrees;

		//Converts encoder degrees to distance in inches
		leftEncoderDistance = leftEncoderDegreesDifference * M_PI / 180.0 * WHEEL_DIAMETER / 2.0;
		rightEncoderDistance = rightEncoderDegreesDifference * M_PI / 180.0 * WHEEL_DIAMETER / 2.0;
		backEncoderDistance = backEncoderDegreesDifference * M_PI / 180.0 * WHEEL_DIAMETER / 2.0;

		//Gets heading values from inertial
		inertLeft = abs(imuLeft.get_heading()) * M_PI / 180;
		inertRight = abs(imuRight.get_heading()) * M_PI / 180;
		inertCenter = abs(imuCenter.get_heading()) * M_PI / 180;
		//Checks if calibration in complete
		if (inertLeft != INFINITY && inertRight != INFINITY && inertCenter != INFINITY)
		{
			//Calculates average of inertial readings
			theta = headingAverageBeta(inertLeft, inertRight, inertCenter);
			// theta = averageHeadings(inertLeft, inertRight, inertCenter);
			// theta = inertRight + calcAngleDiff(inertLeft, inertRight) / 2;

			//Adjusts theta to be between 0 and 2pi
			while (theta > M_PI * 2)
			{
				theta -= M_PI * 2;
			}
			while (theta < 0)
			{
				theta += M_PI * 2;
			}
		}

		//Calculates change in heading during previous cycle
		deltaTheta = (leftEncoderDistance - rightEncoderDistance) / (DISTANCE_TO_LEFT_ENCODER + DISTANCE_TO_RIGHT_ENCODER);

		//Uses delta theta to calculate relative changes in x and y
		if (deltaTheta != 0)
		{
			x = 2 * sin(deltaTheta / 2.0) * (backEncoderDistance / deltaTheta + DISTANCE_TO_BACK_ENCODER);
			y = 2 * sin(deltaTheta / 2.0) * (rightEncoderDistance / deltaTheta + DISTANCE_TO_RIGHT_ENCODER);
		}
		else
		{
			x = backEncoderDistance;
			y = rightEncoderDistance;
		}

		//Calculates average heading during previous cycle
		thetaM = theta - deltaTheta / 2;

		//Rotates relative changes in x and y onto global coordinate grid
		newX = x * cos(-thetaM) - y * sin(-thetaM);
		newY = y * cos(-thetaM) + x * sin(-thetaM);

		//Finds new coordinates by adjusting previous coordinates by change values
		positionVector[0] = positionVector[0] + newX;
		positionVector[1] = positionVector[1] + newY;

		printf("IMUs: %.3f, %.3f, %.3f\n", inertLeft * 180 / M_PI, inertRight * 180 / M_PI, inertCenter * 180 / M_PI);
		printf("Coordinates: %.3f, %.3f, %.3f\n", positionVector[0], positionVector[1], theta * 180 / M_PI);
		pros::delay(10);
	}
}

/**
 * Resets all positioning variables back to 0
 */
void PositionAlg::resetGlobal()
{
	previousLeftEncoderDegrees = 0;
	previousRightEncoderDegrees = 0;
	previousBackEncoderDegrees = 0;

	leftEncoderDegrees = 0;
	rightEncoderDegrees = 0;
	backEncoderDegrees = 0;

	leftEncoderDegreesDifference = 0;
	rightEncoderDegreesDifference = 0;
	backEncoderDegreesDifference = 0;

	leftEncoderRadians = 0;
	rightEncoderRadians = 0;
	backEncoderRadians = 0;

	leftEncoderDistance = 0;
	rightEncoderDistance = 0;
	backEncoderDistance = 0;

	deltaTheta = 0;
	polarTheta = 0;

	positionVector[0] = 0;
	positionVector[1] = 0;
	newVector[0] = 0;
	newVector[1] = 0;

	x = 0;
	y = 0;
	r = 0;
	theta = 0;
	thetaM = 0;
	newX = 0;
	newY = 0;
}
