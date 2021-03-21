#include "positioning/positionController.h"

double PositionController::WHEEL_DIAMETER = 2.75;
double PositionController::DISTANCE_TO_LEFT_ENCODER = 6.125;
double PositionController::DISTANCE_TO_RIGHT_ENCODER = 6.125;
double PositionController::DISTANCE_TO_BACK_ENCODER = 6.0625;

double PositionController::previousLeftEncoderDegrees = 0;
double PositionController::previousRightEncoderDegrees = 0;
double PositionController::previousBackEncoderDegrees = 0;

double PositionController::leftEncoderDegrees = 0;
double PositionController::rightEncoderDegrees = 0;
double PositionController::backEncoderDegrees = 0;

double PositionController::leftEncoderDegreesDifference = 0;
double PositionController::rightEncoderDegreesDifference = 0;
double PositionController::backEncoderDegreesDifference = 0;

double PositionController::leftEncoderRadians = 0;
double PositionController::rightEncoderRadians = 0;
double PositionController::backEncoderRadians = 0;

double PositionController::leftEncoderDistance = 0;
double PositionController::rightEncoderDistance = 0;
double PositionController::backEncoderDistance = 0;

double PositionController::deltaTheta = 0;
double PositionController::polarTheta = 0;
double PositionController::theta = 0;
double PositionController::thetaOdom = 0;

double PositionController::robotSpeed = 0;

vector<double> PositionController::positionVector = { 0, 0 };
vector<double> PositionController::newVector = { 0, 0 };

vector<double> PositionController::testVector(1000, -1);
vector<double> PositionController::leftVector(1000, 999999);
vector<double> PositionController::rightVector(1000, 9999999);

double PositionController::x;
double PositionController::y;
double PositionController::r;
double PositionController::newX;
double PositionController::newY;
double PositionController::thetaM;

double PositionController::inertLeft = 0;
double PositionController::inertLeftOffset = 0;
double PositionController::inertRight = 0;
double PositionController::inertRightOffset = 0;
double PositionController::inertCenter = 0;
double PositionController::inertCenterOffset = 0;

PositionController::PositionController(){
	
}

/**
 * Returns robot heading
 */
double PositionController::getTheta()
{
	return theta;
}

/**
 * Returns robot heading, measured with encoders
 */
double PositionController::getThetaOdom()
{
	return thetaOdom;
}

/**
 * Returns robot position
 */
vector<double> PositionController::getPosition()
{
	return positionVector;
}

/**
 * Returns robot speed
 */
double PositionController::getSpeed()
{
	return robotSpeed;
}

/**
 * Calculates robot position using odometry algorithm
 */
void PositionController::calcPosition(void* ignore)
{

	while (true)
	{
		//Gets raw values from encoders
		leftEncoderDegrees = leftEncoder.get_value();
		rightEncoderDegrees = rightEncoder.get_value();
		backEncoderDegrees = backEncoder.get_value();

		// printf("Encoders: %.3f, %.3f, %.3f\n", leftEncoderDegrees, rightEncoderDegrees, backEncoderDegrees);

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
		inertLeft = fmod((abs(imuLeft.get_heading()) * M_PI / 180 + inertLeftOffset), (2 * M_PI));
		inertRight = fmod((abs(imuRight.get_heading()) * M_PI / 180 + inertRightOffset), (2 * M_PI));
		inertCenter = fmod((abs(imuCenter.get_heading()) * M_PI / 180 + inertCenterOffset), (2 * M_PI));
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

		thetaOdom += deltaTheta;

		while (thetaOdom > M_PI * 2)
		{
			thetaOdom -= M_PI * 2;
		}
		while (thetaOdom < 0)
		{
			thetaOdom += M_PI * 2;
		}

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

		//Calculates the robot's velocity
		robotSpeed = sqrt(pow(newX, 2) + pow(newY, 2)) * 2.54;

		//Finds new coordinates by adjusting previous coordinates by change values
		positionVector[0] = positionVector[0] + newX;
		positionVector[1] = positionVector[1] + newY;

		//printf("Coordinates: %.3f, %.3f, %.3f\n", positionVector[0], positionVector[1], theta * 180 / M_PI);
		pros::delay(10);
	}
}

/**
 * Resets all positioning variables back to 0
 */
void PositionController::resetGlobal()
{
	//Reset encoder values
	leftEncoder.reset();
	rightEncoder.reset();
	backEncoder.reset();

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

	positionVector = { 0, 0 };
	newVector = { 0, 0 };

	x = 0;
	y = 0;
	r = 0;
	newX = 0;
	newY = 0;
}

/**
 * Sets theta to a given value by offsetting each inertial sensor
 */
void PositionController::setTheta(double newTheta)
{
	inertLeftOffset = newTheta - inertLeft + inertLeftOffset;
	inertRightOffset = newTheta - inertRight + inertRightOffset;
	inertCenterOffset = newTheta - inertCenter + inertCenterOffset;
	while (inertLeftOffset < 0) {
		inertLeftOffset += 2 * M_PI;
	}
	while (inertRightOffset < 0) {
		inertRightOffset += 2 * M_PI;
	}
	while (inertCenterOffset < 0) {
		inertCenterOffset += 2 * M_PI;
	}
}

void PositionController::setThetaOdom(double newTheta){
	thetaOdom = newTheta;
}

/**
 * Sets the position to a given value
 */
void PositionController::setPosition(double x, double y)
{
	positionVector = { x,y };
}
