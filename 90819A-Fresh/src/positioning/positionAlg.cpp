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

vector<double> positionVector = {0, 0};
vector<double> newVector = {0, 0};

vector<double> testVector(1000, -1);
vector<double> leftVector(1000, 999999);
vector<double> rightVector(1000, 9999999);

double x;
double y;
double r;
double theta;
double newX;
double newY;
double thetaM;

double inertLast = 0;
double inertLeft = 0;
double inertRight = 0;
double inertTheta = 0;
int count2 = 0;

Inertial imu;

// bool spaghetti = imu.initialize();
// pros::Task imuController(imu.calcAngle, NULL, "Inertial Tracker");

double PositionAlg::getTheta()
{
	return theta;
}

double PositionAlg::getThetaInertial()
{
	return imu.getTheta();
}

vector<double> PositionAlg::getPosition()
{
	return positionVector;
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

void PositionAlg::calcPosition(void *ignore)
{

	// double offset = 0;
	while (true)
	{
		leftEncoderDegrees = leftEncoder.get_value();
		rightEncoderDegrees = rightEncoder.get_value();
		backEncoderDegrees = backEncoder.get_value();

		leftEncoderDegreesDifference = leftEncoderDegrees - previousLeftEncoderDegrees;
		rightEncoderDegreesDifference = rightEncoderDegrees - previousRightEncoderDegrees;
		backEncoderDegreesDifference = backEncoderDegrees - previousBackEncoderDegrees;

		previousLeftEncoderDegrees = leftEncoderDegrees;
		previousRightEncoderDegrees = rightEncoderDegrees;
		previousBackEncoderDegrees = backEncoderDegrees;

		leftEncoderDistance = leftEncoderDegreesDifference * M_PI / 180.0 * WHEEL_DIAMETER / 2.0;
		rightEncoderDistance = rightEncoderDegreesDifference * M_PI / 180.0 * WHEEL_DIAMETER / 2.0;
		backEncoderDistance = backEncoderDegreesDifference * M_PI / 180.0 * WHEEL_DIAMETER / 2.0;

		// printf("Left: %.3f\n", leftEncoderDegrees * M_PI / 180.0 * WHEEL_DIAMETER / 2);
		// printf("right: %.3f\n", rightEncoderDegrees * M_PI / 180.0 * WHEEL_DIAMETER / 2);
		// printf("Back: %.3f\n", backEncoderDegrees * M_PI / 180.0 * WHEEL_DIAMETER / 2);

		inertLeft = abs(imuLeft.get_heading()) * M_PI / 180;
		inertRight = abs(imuRight.get_heading()) * M_PI / 180;

		// printf("inertLeft: %.3f\n", inertLeft * 180 / M_PI);
		// printf("inertRight: %.3f\n", inertRight * 180 / M_PI);


		if (inertLeft != INFINITY && inertRight != INFINITY)
		{
			inertTheta = inertRight + calcAngleDiff(inertLeft, inertRight) / 2;

			while (inertTheta > M_PI * 2)
			{
				inertTheta -= M_PI * 2;
			}
			while (theta < 0)
			{
				inertTheta += M_PI * 2;
			}
			// deltaTheta = calcAngleDiff(inertTheta, inertLast);
			// printf("deltaTheta1: %.3f\n", deltaTheta);
			inertLast = inertTheta;
			theta = inertTheta;
		}

		deltaTheta = (leftEncoderDistance - rightEncoderDistance) / (DISTANCE_TO_LEFT_ENCODER + DISTANCE_TO_RIGHT_ENCODER);

		// printf("deltaTheta2: %.3f\n", deltaTheta);


		// theta += deltaTheta;

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

		while (theta > M_PI * 2)
		{
			theta -= M_PI * 2;
		}
		while (theta < 0)
		{
			theta += M_PI * 2;
		}

		//rotate by negative theta, convert back

		thetaM = theta - deltaTheta / 2;

		newX = x * cos(-thetaM) - y * sin(-thetaM);
		newY = y * cos(-thetaM) + x * sin(-thetaM);

		positionVector[0] = positionVector[0] + newX;
		positionVector[1] = positionVector[1] + newY;

		//printf("x-coordinate: %.3f\n", positionVector[0]);
		//printf("y-coordinate: %.3f\n", positionVector[1]);
		//printf("change in raw x: %.3f\n", x);
		//printf("change in raw y: %.3f\n", y);
		//printf("change in x: %.3f\n", newX);
		//printf("change in y: %.3f\n", newY);
		// printf("x: %.3f\n", positionVector[0]);
		// printf("y: %.3f\n", positionVector[1]);
		// printf("theta: %.3f\n", theta * 180.0 / M_PI);
		// printf("inertTheta: %.3f\n", inertTheta * 180 / M_PI);

		// printf("line Sensor: %d\n", lineSensor.get_value());
		pros::delay(10);
		count2 += 1;
	}
}

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
