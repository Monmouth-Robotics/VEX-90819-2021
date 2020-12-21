#include "motion/purePursuit/pathFollowing.h"

/*
Creates function that takes in current x, y, and theta and lookahead point x, y, theta, and returns proper error.
Function rotates the lookahead position about the robot origin.
*/

vector<double> getErrors(vector<double> currentPosition, vector<double> lookAheadPosition)
{
	vector<double> adjustedError = {0, 0, 0};

	//calculates new x coordinate
	double rotatedX = cos(currentPosition[2]) * (lookAheadPosition[0] - currentPosition[0]) - sin(currentPosition[2]) * (lookAheadPosition[1] - currentPosition[1]) + currentPosition[0];
	//calculates new y coordinate
	double rotatedY = sin(currentPosition[2]) * (lookAheadPosition[0] - currentPosition[0]) + cos(currentPosition[2]) * (lookAheadPosition[1] - currentPosition[1]) + currentPosition[1];

	//calculates x error
	double xError = rotatedX - currentPosition[0];
	//calculates y error
	double yError = rotatedY - currentPosition[1];
	//calculates angle error
	double angleError = calcAngleDiff(lookAheadPosition[2], currentPosition[2]);

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

void moveRobot(vector<double> errors, double distanceError, double kPDistance, double kPAngle, double kDDistance, double kDAngle, double kIDistance, double kIAngle, double lastDistanceError, double lastAngleError, double integralDistanceError, double integralAngleError)
{
	double maxPower = kPDistance * distanceError; //127

	if (maxPower > 127)
	{
		maxPower = 127;
	}
	else if (maxPower < -127)
	{
		maxPower = -127;
	}
	double xError = errors[0];
	double yError = errors[1];
	double angleError = errors[2];
	string distanceString = ((string)("Distance Error: ") + (string)(to_string(distanceError)));
	string thetaString = ((string)("Theta Error: ") + (string)(to_string(angleError)));

	pros::lcd::set_text(5, strcpy(new char[distanceString.length() + 1], distanceString.c_str()));
	pros::lcd::set_text(6, strcpy(new char[thetaString.length() + 1], thetaString.c_str()));

	double leftFrontPower;
	double leftBackPower;
	double rightFrontPower;
	double rightBackPower;

	if (signum(xError) == signum(yError))
	{
		leftFrontPower = maxPower * signum(xError);
		rightBackPower = maxPower * signum(xError);
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

		if (abs(xError) > abs(yError))
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
	// double distancePower = kDDistance * (distanceError - lastDistanceError) + kIAngle * integralDistanceError;
	double anglePower = angleError * kPAngle;
	// + kDAngle * (angleError - lastAngleError) + kIAngle * integralAngleError;

	//printf("kPAngle: %.3f\n", kPAngle);

	// leftFrontPower += distancePower;
	// leftBackPower += distancePower;
	// rightFrontPower += distancePower;
	// rightBackPower += distancePower;

	leftFrontPower += anglePower;
	leftBackPower += anglePower;
	rightFrontPower -= anglePower;
	rightBackPower -= anglePower;

	//Limits voltage of each motor under threshold and scales accordingly
	double maxCurrSpeed = max(max(abs(leftFrontPower), abs(leftBackPower)), max(abs(rightFrontPower), abs(rightBackPower)));
	if (maxCurrSpeed > maxPower)
	{
		leftFrontPower = leftFrontPower * (maxPower / maxCurrSpeed);
		leftBackPower = leftBackPower * (maxPower / maxCurrSpeed);
		rightFrontPower = rightFrontPower * (maxPower / maxCurrSpeed);
		rightBackPower = rightBackPower * (maxPower / maxCurrSpeed);
	}

	leftFrontMotor = leftFrontPower;
	leftBackMotor = leftBackPower;
	rightFrontMotor = rightFrontPower;
	rightBackMotor = rightBackPower;

	// printf("Motor speeds: %.3f, %.3f, %.3f, %.3f\n", leftFrontPower, rightBackPower, rightFrontPower, leftBackPower);
}

vector<double> findLookAheadPoint(double x, double y, vector<vector<double>> pointsList, int closestPoint, int lookAheadPointsNum, double lookAheadDistance)
{
	//Starting point of the line segment
	vector<double> E = {0.0, 0.0};
	E = {pointsList[closestPoint][0], pointsList[closestPoint][1]};

	//End point of the line segment
	vector<double> L = {0.0, 0.0};
	L = {pointsList[closestPoint + lookAheadPointsNum][0], pointsList[closestPoint + lookAheadPointsNum][1]};

	//Center of the drawn circle, representing the robot position
	vector<double> C = {0.0, 0.0};
	C = {x, y};

	//Direction vector from starting point to ending point
	vector<double> d = {0.0, 0.0};
	d = {L[0] - E[0], L[1] - E[1]};

	//Vector drawn from center of robot to starting point
	vector<double> f = {0.0, 0.0};
	f = {E[0] - C[0], E[1] - C[1]};

	//Represents the lookahead distance
	double r = lookAheadDistance;

	//Determines number of intersections between circle around robot and path
	double a = dot(d, d);
	double b = 2 * dot(f, d);
	double c = dot(f, f) - r * r;
	double discriminant = b * b - 4 * a * c;

	if (closestPoint + lookAheadPointsNum < pointsList.size())
	{
		return pointsList[closestPoint + lookAheadPointsNum];
	}
	else{
		return pointsList[pointsList.size()-1];
	}

	//Represents no intersection
	if (discriminant < 0)
	{
		//If the current lookahead point is not the last point, it can expand its search radius
		if (closestPoint != pointsList.size() - lookAheadPointsNum - 1)
		{
			//Recursive function with a greater number of lookahead points
			return findLookAheadPoint(x, y, pointsList, closestPoint, lookAheadPointsNum + 1, lookAheadDistance);
		}
		else
		{
			//Returns the last point in the list
			return pointsList[pointsList.size() - 1];
		}
	}
	else
	{
		//Find points of intersection at t1 and t2
		double t1 = (-b - sqrt(discriminant)) / (2 * a);
		double t2 = (-b + sqrt(discriminant)) / (2 * a);

		//Verifies that the lookahead point is ahead of the current point in the motion
		if (t1 >= 0 && t1 <= 1)
		{
			return {E[0] + t1 * d[0], E[1] + t1 * d[1]};
		}
		else if (t2 >= 0 && t2 <= 1)
		{
			return {E[0] + t2 * d[0], E[1] + t2 * d[1]};
		}
		//Expands search radius if both points found are behind the current point in the motion
		else
		{
			if (closestPoint != pointsList.size() - lookAheadPointsNum - 1)
			{
				//Recursive function with a greater number of lookahead points
				return findLookAheadPoint(x, y, pointsList, closestPoint, lookAheadPointsNum + 1, lookAheadDistance);
			}
			else
			{
				//Returns the last point in the list
				return pointsList[pointsList.size() - 1];
			}
		}
	}
}

void ppMove(vector<vector<double>> initPoints, double spacing, double smoothVal1, double smoothVal2, double smoothTolerance, double maxVel, double maxAccel, double turnConstant, int lookAheadPointsNum, double thresholdError, double angleThreshold, double kPDistance, double kPAngle, double kDDistance, double kDAngle, double kIDistance, double kIAngle)
{
	double distanceError = 999999;
	double angleError = 999999;
	double lastDistanceError = 0.0;
	double lastAngleError = 0.0;
	double integralDistanceError = 0.0;
	double integralAngleError = 0.0;

	vector<vector<double>> pointsList = {{0.0}};
	pointsList = {};

	pointsList = generatePath(initPoints, spacing, smoothVal1, smoothVal2, smoothTolerance, maxVel, maxAccel, turnConstant);
	vector<double> errors = {0, 0, 0};
	// errors = {};
	// printf("here");
	int closestPoint = 1;

	// printf("here\n");
	while (distanceError > thresholdError || angleError > angleThreshold)
	{
		double x = position.getPosition()[0];
		double y = position.getPosition()[1];

		distanceError = distanceFormula({x, y}, pointsList[pointsList.size() - 1]);
		// //Pulls the current robot coordinates

		//Initialize lookahead point as empty vector
		vector<double> lookAheadPoint = {0, 0, 0};
		lookAheadPoint = {};

		//Calculate distance between closest point and current robot position
		double smallestDistance = sqrt(pow((pointsList[closestPoint][0] - x), 2) + pow((pointsList[closestPoint][1] - y), 2));

		//Traverse through every point to find the closest point to the robot
		//For loop starts at closestPoint+1 to avoid traveling backwards
		for (int i = closestPoint + 1; i < pointsList.size(); i++)
		{
			//Calculates distance between current robot and each point after closest point
			double newDistance = sqrt(pow((pointsList[i][0] - x), 2) + pow((pointsList[i][1] - y), 2));

			//If the new distance is smaller than the smallest distance, replace smallest distance value with the new distance
			if (smallestDistance > newDistance)
			{
				smallestDistance = newDistance;

				//Change closest point to the new closest point
				closestPoint = i;
			}
		}

		//Calculate lookahead point if the last point is not within the default search radius
		if (closestPoint < pointsList.size() - 1 - lookAheadPointsNum)
		{
			lookAheadPoint = findLookAheadPoint(x, y, pointsList, closestPoint, lookAheadPointsNum, spacing * lookAheadPointsNum);
		}

		//Use last point as lookahead point if the last point is within the default search radius
		else
		{
			lookAheadPoint = pointsList[pointsList.size() - 1];
		}
		// vector<double> errorArg1 = {0.0};
		// errorArg1 = position.getPosition();

		errors = getErrors({x, y, position.getTheta()}, lookAheadPoint);
		angleError = errors[2];
		// printf("Errors: %.3f, %.3f, %.3f\n", errors[0], errors[1], errors[2]);
		integralAngleError += angleError;
		integralDistanceError += distanceError;
		moveRobot(errors, distanceError, kPDistance, kPAngle, kDDistance, kDAngle, kIDistance, kIAngle, lastDistanceError, lastAngleError, integralDistanceError, integralAngleError);
		lastDistanceError = distanceError;
		lastAngleError = angleError;
		// errors = {5, 0};
		// printf("Position: %.3f, %.3f, %.3f\n", x, y, position.getTheta());
		// printf("Lookahead point: %.3f, %.3f\n", lookAheadPoint[0], lookAheadPoint[1]);
		// printf("Closest point: %.3f, %.3f\n", pointsList[closestPoint][0], pointsList[closestPoint][1]);

		pros::delay(10);
	}

	leftFrontMotor = 0;
	leftBackMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;

	//Exits loop if lookahead point and closest point align with the last point of the path
	// if (lookAheadPoint[0] == pointsList[pointsList.size() - 1][0] && lookAheadPoint[1] == pointsList[pointsList.size() - 1][1] && (closestPoint == pointsList.size() - 1))
	// {
	//     break;
	// }
}