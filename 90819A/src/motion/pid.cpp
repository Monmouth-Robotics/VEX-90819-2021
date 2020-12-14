#include "motion/pid.h"

/**
 * Turns using PID control
 * 
 * Parameters:
 * target: target heading
 * maxVel: max voltage supplied to motors
 * thresholdError: threshold error before stopping motion
 * kP: proportional constant
 * kI: integral constant
 * kD: derivative constant
 */
void pidTurn(double target, double maxVel, double thresholdError, double kP, double kI, double kD)
{
	double error = 999999;
	double lastError = 0;
	double integralLimit = 0;
	double integral = 0;
	double derivative = 0;
	double power = 0;

	while (abs(error) > thresholdError)
	{
		error = calcAngleDiff(target, position.getTheta());

		//Calculates integral error
		if (kI != 0)
		{
			if (abs(error) < integralLimit)
			{
				integral += error;
			}
			else
			{
				integral = 0;
			}
		}
		else
		{
			integral = 0;
		}

		//Calculates derivative error
		derivative = error - lastError;
		lastError = error;
		
		//Calculates motor voltage using PID constants
		power = kP * error + kI * integral + kD * derivative;
		
		//Limits calculated voltage under maximum
		if (power > maxVel)
			power = maxVel;
		if (power < -maxVel)
			power = -maxVel;

		//Supplies voltages to motors
		leftBackMotor = power;
		leftFrontMotor = power;
		rightBackMotor = -power;
		rightFrontMotor = -power;

		pros::delay(10);
	}

	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightBackMotor = 0;
	rightFrontMotor = 0;
}

/**
 * Moves forward using PID control
 * 
 * Parameters:
 * targetTheta: target heading for motion
 * distanceLine: list of points to generate ideal path
 * maxVel: max voltage supplied to motors
 * thresholdDistanceError: threshold distance error before stopping motion
 * kpAngle: proportional constant for angle
 * kPDistance: proportional constant for distance
 * kPDiff: proportional constant for strafing
 * kIAngle: integral constant for angle
 * kIDistance: integral constant for distance
 * kIDiff: integral constant for strafing
 * kDAngle: derivative constant for angle
 * kDDistance: derivative constant for distance
 * kDDiff: derivative constant for strafing
 * stopMotors: specifies whether to stop motors at end of motion
 */
void pidForward(double targetTheta, vector<vector<double>> distanceLine, double maxVel, double thresholdDistanceError, double kPAngle, double kPDistance, double kPDiff, double kIAngle, double kIDistance, double kIDiff, double kDAngle, double kDDistance, double kDDiff, bool stopMotors)
{
	double distanceError = 99999999;
	double angleError = 99999;
	double diffError = 99999;
	double lastDistanceError = 0.0;
	double lastAngleError = 0.0;
	double lastDiffError = 0.0;
	double powerAngle = 0.0;
	double powerDistance = 0.0;
	double powerDiff = 0.0;
	double integralLimitAngle = 0.0;
	double integralLimitDistance = 0.0;
	double integralLimitDiff = 0.0;
	double integralAngle = 0.0;
	double integralDistance = 0.0;
	double integralDiff = 0.0;
	double derivativeAngle = 0.0;
	double derivativeDistance = 0.0;
	double derivativeDiff = 0.0;

	double m;

	//Calculates slope of target line
	if (distanceLine[0][0] == distanceLine[1][0])
	{
		m = WINT_MAX;
	}
	else
	{
		m = (distanceLine[0][1] - distanceLine[1][1]) / (distanceLine[0][0] - distanceLine[1][0]);
	}

	//Calculates equation of target line
	double tempB = distanceLine[0][1] - m * distanceLine[0][0];
	double a = -1 * m;
	double b = 1;
	double c = -tempB;

	//Rotates target line to face towards heading of 0
	double origTheta = atan(m);
	double p = -1 * c / sqrt(pow(a, 2) + pow(b, 2));
	double beta = M_PI / 2;
	double rotatedA = sin(beta);
	double rotatedB = cos(beta);
	double rotatedC = -1 * p;

	//Calculates end coordinates post-rotation
	double hypEndpoint = sqrt(pow((distanceLine[1][0]), 2) + pow((distanceLine[1][1]), 2));
	double rotatedEndX = distanceLine[1][0] * cos(beta - origTheta) - distanceLine[1][1] * sin(beta - origTheta);
	double rotatedEndY = distanceLine[1][0] * sin(beta - origTheta) + distanceLine[1][1] * cos(beta - origTheta);

	while (abs(distanceError) > thresholdDistanceError)
	{
		//Gets robot's current coordinates and heading
		double currX = position.getPosition()[0];
		double currY = position.getPosition()[1];
		double currTheta = position.getTheta();

		//Calculates rotated coordinates and headings
		double adjThetaRobot = currTheta + beta - origTheta;
		double rotatedCurrX = currX * cos(beta - origTheta) - currY * sin(beta - origTheta);
		double rotatedCurrY = currX * sin(beta - origTheta) + currY * cos(beta - origTheta);
		
		//Calculates angle error
		angleError = calcAngleDiff(targetTheta, currTheta);

		//Calculates distance error from closest point on target line to endpoint
		distanceError = abs(rotatedEndY - rotatedCurrY);

		//Calculates strafe error from closest point on target line to endpoint
		diffError = rotatedEndX - rotatedCurrX;

		//Calculates integral error for angle
		if (kIAngle != 0)
		{
			if (abs(angleError) < integralLimitAngle)
			{
				integralAngle += angleError;
			}
			else
			{
				integralAngle = 0;
			}
		}
		else
		{
			integralAngle = 0;
		}

		//Calculates derivative error for angle
		derivativeAngle = angleError - lastAngleError;
		lastAngleError = angleError;

		//Calculates angle voltage using PID constants
		powerAngle = kPAngle * angleError + kIAngle * integralAngle + kDAngle * derivativeAngle;

		//Calculates integral error for distance
		if (kIDistance != 0)
		{
			if (abs(distanceError) < integralLimitDistance)
			{
				integralDistance += distanceError;
			}
			else
			{
				integralDistance = 0;
			}
		}
		else
		{
			integralDistance = 0;
		}

		//Calculates derivative error for distance
		derivativeDistance = distanceError - lastDistanceError;
		lastDistanceError = distanceError;

		//Calculates distance voltage using PID constants 
		powerDistance = kPDistance * distanceError + kIDistance * integralDistance + kDDistance * derivativeDistance;

		//Calculates integral error for strafing
		if (kIDiff != 0)
		{
			if (abs(diffError) < integralLimitDiff)
			{
				integralDiff += diffError;
			}
			else
			{
				integralDiff = 0;
			}
		}
		else
		{
			integralDiff = 0;
		}

		//Calculates derivative error for strafing
		derivativeDiff = diffError - lastDiffError;
		lastDiffError = diffError;

		//Calculates voltage for strafing using PID constants
		powerDiff = kPDiff * diffError + kIDiff * integralDiff + kDDiff * derivativeDiff;

		//Calculates target voltage for each wheel using angle, distance, and strafe voltages
		double leftFrontSpeed = powerDistance + powerAngle + powerDiff;
		double leftBackSpeed = powerDistance + powerAngle - powerDiff;
		double rightFrontSpeed = powerDistance - powerAngle - powerDiff;
		double rightBackSpeed = powerDistance - powerAngle + powerDiff;

		//Limits voltage of each motor under threshold and scales accordingly
		double maxCurrSpeed = max(max(abs(leftFrontSpeed), abs(leftBackSpeed)), max(abs(rightFrontSpeed), abs(rightBackSpeed)));	
		if (maxCurrSpeed > maxVel)
		{
			leftFrontSpeed = leftFrontSpeed * (maxVel / maxCurrSpeed);
			leftBackSpeed = leftBackSpeed * (maxVel / maxCurrSpeed);
			rightFrontSpeed = rightFrontSpeed * (maxVel / maxCurrSpeed);
			rightBackSpeed = rightBackSpeed * (maxVel / maxCurrSpeed);
		}

		//Supplies voltages to motors
		leftFrontMotor = leftFrontSpeed;
		leftBackMotor = leftBackSpeed;
		rightFrontMotor = rightFrontSpeed;
		rightBackMotor = rightBackSpeed;

		pros::delay(10);
	}

	//Stops motors at end of motion
	if (stopMotors)
	{
		leftFrontMotor = 0;
		leftBackMotor = 0;
		rightFrontMotor = 0;
		rightBackMotor = 0;
	}
}

/**
 * Moves backward using PID control
 * 
 * Parameters:
 * targetTheta: target heading for motion
 * distanceLine: list of points to generate ideal path
 * maxVel: max voltage supplied to motors
 * thresholdDistanceError: threshold distance error before stopping motion
 * kpAngle: proportional constant for angle
 * kPDistance: proportional constant for distance
 * kPDiff: proportional constant for strafing
 * kIAngle: integral constant for angle
 * kIDistance: integral constant for distance
 * kIDiff: integral constant for strafing
 * kDAngle: derivative constant for angle
 * kDDistance: derivative constant for distance
 * kDDiff: derivative constant for strafing
 * stopMotors: specifies whether to stop motors at end of motion
 */
void pidBackward(double targetTheta, vector<vector<double>> distanceLine, double maxVel, double thresholdDistanceError, double kPAngle, double kPDistance, double kPDiff, double kIAngle, double kIDistance, double kIDiff, double kDAngle, double kDDistance, double kDDiff, bool stopMotors)
{
	double distanceError = 99999999;
	double angleError = 99999;
	double diffError = 99999;
	double lastDistanceError = 0.0;
	double lastAngleError = 0.0;
	double lastDiffError = 0.0;
	double powerAngle = 0.0;
	double powerDistance = 0.0;
	double powerDiff = 0.0;
	double integralLimitAngle = 0.0;
	double integralLimitDistance = 0.0;
	double integralLimitDiff = 0.0;
	double integralAngle = 0.0;
	double integralDistance = 0.0;
	double integralDiff = 0.0;
	double derivativeAngle = 0.0;
	double derivativeDistance = 0.0;
	double derivativeDiff = 0.0;

	double m;

	//Calculates slope of target line
	if (distanceLine[0][0] == distanceLine[1][0])
	{
		m = WINT_MAX;
	}
	else
	{
		m = (distanceLine[0][1] - distanceLine[1][1]) / (distanceLine[0][0] - distanceLine[1][0]);
	}

	//Calculates equation of target line
	double tempB = distanceLine[0][1] - m * distanceLine[0][0];
	double a = -1 * m;
	double b = 1;
	double c = -tempB;

	//Rotates target line to face towards heading of 0
	double origTheta = atan(m);
	double p = -1 * c / sqrt(pow(a, 2) + pow(b, 2));
	double beta = M_PI / 2;
	double rotatedA = sin(beta);
	double rotatedB = cos(beta);
	double rotatedC = -1 * p;

	//Calculates end coordinates post-rotation
	double hypEndpoint = sqrt(pow((distanceLine[1][0]), 2) + pow((distanceLine[1][1]), 2));
	double rotatedEndX = distanceLine[1][0] * cos(beta - origTheta) - distanceLine[1][1] * sin(beta - origTheta);
	double rotatedEndY = distanceLine[1][0] * sin(beta - origTheta) + distanceLine[1][1] * cos(beta - origTheta);

	while (abs(distanceError) > thresholdDistanceError)
	{	
		//Gets robot's current coordinates and heading
		double currX = position.getPosition()[0];
		double currY = position.getPosition()[1];
		double currTheta = position.getTheta();

		//Calculates rotated coordinates and headings
		double adjThetaRobot = currTheta + beta - origTheta;
		double rotatedCurrX = currX * cos(beta - origTheta) - currY * sin(beta - origTheta);
		double rotatedCurrY = currX * sin(beta - origTheta) + currY * cos(beta - origTheta);

		//Calculates angle error
		angleError = calcAngleDiff(targetTheta, currTheta);
				
				
		//Calculates distance error from closest point on target line to endpoint
		distanceError = abs(rotatedEndY - rotatedCurrY);

		//Calculates strafe error from closest point on target line to endpoint
		diffError = rotatedEndX - rotatedCurrX;

		//Calculates integral error for angle
		if (kIAngle != 0)
		{
			if (abs(angleError) < integralLimitAngle)
			{
				integralAngle += angleError;
			}
			else
			{
				integralAngle = 0;
			}
		}
		else
		{
			integralAngle = 0;
		}

		//Calculates derivative error for angle
		derivativeAngle = angleError - lastAngleError;
		lastAngleError = angleError;

		//Calculates angle voltage using PID constants
		powerAngle = kPAngle * angleError + kIAngle * integralAngle + kDAngle * derivativeAngle;

		//Calculates integral error for distance
		if (kIDistance != 0)
		{
			if (abs(distanceError) < integralLimitDistance)
			{
				integralDistance += distanceError;
			}
			else
			{
				integralDistance = 0;
			}
		}
		else
		{
			integralDistance = 0;
		}

		//Calculates derivative error for distance
		derivativeDistance = distanceError - lastDistanceError;
		lastDistanceError = distanceError;

		//Calculates distance voltage using PID constants 
		powerDistance = kPDistance * distanceError + kIDistance * integralDistance + kDDistance * derivativeDistance;

		//Calculates integral error for strafing
		if (kIDiff != 0)
		{
			if (abs(diffError) < integralLimitDiff)
			{
				integralDiff += diffError;
			}
			else
			{
				integralDiff = 0;
			}
		}
		else
		{
			integralDiff = 0;
		}

		//Calculates derivative error for strafing
		derivativeDiff = diffError - lastDiffError;
		lastDiffError = diffError;

		//Calculates voltage for strafing using PID constants
		powerDiff = kPDiff * diffError + kIDiff * integralDiff + kDDiff * derivativeDiff;
		
		//Calculates target voltage for each wheel using angle, distance, and strafe voltages
		double leftFrontSpeed = -powerDistance + powerAngle + powerDiff;
		double leftBackSpeed = -powerDistance + powerAngle - powerDiff;
		double rightFrontSpeed = -powerDistance - powerAngle - powerDiff;
		double rightBackSpeed = -powerDistance - powerAngle + powerDiff;

		//Limits voltage of each motor under threshold and scales accordingly
		double maxCurrSpeed = max(max(abs(leftFrontSpeed), abs(leftBackSpeed)), max(abs(rightFrontSpeed), abs(rightBackSpeed)));
		if (maxCurrSpeed > maxVel)
		{
			leftFrontSpeed = leftFrontSpeed * (maxVel / maxCurrSpeed);
			leftBackSpeed = leftBackSpeed * (maxVel / maxCurrSpeed);
			rightFrontSpeed = rightFrontSpeed * (maxVel / maxCurrSpeed);
			rightBackSpeed = rightBackSpeed * (maxVel / maxCurrSpeed);
		}

		//Supplies voltages to motors
		leftFrontMotor = leftFrontSpeed;
		leftBackMotor = leftBackSpeed;
		rightFrontMotor = rightFrontSpeed;
		rightBackMotor = rightBackSpeed;

		pros::delay(10);
	}

	//Stops motors at end of motion
	if (stopMotors)
	{
		leftFrontMotor = 0;
		leftBackMotor = 0;
		rightFrontMotor = 0;
		rightBackMotor = 0;
	}
}

/**
 * Strafes right using PID control
 * 
 * Parameters:
 * targetTheta: target heading for motion
 * distanceLine: list of points to generate ideal path
 * maxVel: max voltage supplied to motors
 * thresholdDistanceError: threshold distance error before stopping motion
 * kpAngle: proportional constant for angle
 * kPDistance: proportional constant for distance
 * kPDiff: proportional constant for forward/backward correction
 * kIAngle: integral constant for angle
 * kIDistance: integral constant for distance
 * kIDiff: integral constant for forward/backward correction
 * kDAngle: derivative constant for angle
 * kDDistance: derivative constant for distance
 * kDDiff: derivative constant for forward/backward correction
 * stopMotors: specifies whether to stop motors at end of motion
 */
void pidRight(double targetTheta, vector<vector<double>> distanceLine, double maxVel, double thresholdDistanceError, double kPAngle, double kPDistance, double kPDiff, double kIAngle, double kIDistance, double kIDiff, double kDAngle, double kDDistance, double kDDiff, bool stopMotors)
{
	double distanceError = 99999999;
	double angleError = 99999;
	double diffError = 99999;
	double lastDistanceError = 0.0;
	double lastAngleError = 0.0;
	double lastDiffError = 0.0;
	double powerAngle = 0.0;
	double powerDistance = 0.0;
	double powerDiff = 0.0;
	double integralLimitAngle = 0.0;
	double integralLimitDistance = 0.0;
	double integralLimitDiff = 0.0;
	double integralAngle = 0.0;
	double integralDistance = 0.0;
	double integralDiff = 0.0;
	double derivativeAngle = 0.0;
	double derivativeDistance = 0.0;
	double derivativeDiff = 0.0;

	double m;

	//Calculates slope of target line
	if (distanceLine[0][0] == distanceLine[1][0])
	{
		m = WINT_MAX;
	}
	else
	{
		m = (distanceLine[0][1] - distanceLine[1][1]) / (distanceLine[0][0] - distanceLine[1][0]);
	}

	//Calculates equation of target line
	double tempB = distanceLine[0][1] - m * distanceLine[0][0];
	double a = -1 * m;
	double b = 1;
	double c = -tempB;

	//Rotates target line to face towards heading of 0
	double origTheta = atan(m);
	double p = -1 * c / sqrt(pow(a, 2) + pow(b, 2));
	double beta = M_PI / 2;
	double rotatedA = sin(beta);
	double rotatedB = cos(beta);
	double rotatedC = -1 * p;

	//Calculates end coordinates post-rotation
	double hypEndpoint = sqrt(pow((distanceLine[1][0]), 2) + pow((distanceLine[1][1]), 2));
	double rotatedEndX = distanceLine[1][0] * cos(beta - origTheta) - distanceLine[1][1] * sin(beta - origTheta);
	double rotatedEndY = distanceLine[1][0] * sin(beta - origTheta) + distanceLine[1][1] * cos(beta - origTheta);


	while (abs(distanceError) > thresholdDistanceError)
	{	
		//Gets robot's current coordinates and heading
		double currX = position.getPosition()[0];
		double currY = position.getPosition()[1];
		double currTheta = position.getTheta();

		//Calculates rotated coordinates and headings
		double adjThetaRobot = currTheta + beta - origTheta;
		double rotatedCurrX = currX * cos(beta - origTheta) - currY * sin(beta - origTheta);
		double rotatedCurrY = currX * sin(beta - origTheta) + currY * cos(beta - origTheta);

		//Calculates angle error
		angleError = calcAngleDiff(targetTheta, currTheta);

		//Calculates distance error from closest point on target line to endpoint
		distanceError = abs(rotatedEndY - rotatedCurrY);

		//Calculates forward/backward error from closest point on target line to endpoint
		diffError = rotatedEndX - rotatedCurrX;

		//Calculates integral error for angle
		if (kIAngle != 0)
		{
			if (abs(angleError) < integralLimitAngle)
			{
				integralAngle += angleError;
			}
			else
			{
				integralAngle = 0;
			}
		}
		else
		{
			integralAngle = 0;
		}

		//Calculates derivative error for angle
		derivativeAngle = angleError - lastAngleError;
		lastAngleError = angleError;

		//Calculates angle voltage using PID constants
		powerAngle = kPAngle * angleError + kIAngle * integralAngle + kDAngle * derivativeAngle;

		//Calculates integral error for distance
		if (kIDistance != 0)
		{
			if (abs(distanceError) < integralLimitDistance)
			{
				integralDistance += distanceError;
			}
			else
			{
				integralDistance = 0;
			}
		}
		else
		{
			integralDistance = 0;
		}

		//Calculates derivative error for distance
		derivativeDistance = distanceError - lastDistanceError;
		lastDistanceError = distanceError;

		//Calculates distance voltage using PID constants 
		powerDistance = kPDistance * distanceError + kIDistance * integralDistance + kDDistance * derivativeDistance;

		//Calculates integral error for forward/backward
		if (kIDiff != 0)
		{
			if (abs(diffError) < integralLimitDiff)
			{
				integralDiff += diffError;
			}
			else
			{
				integralDiff = 0;
			}
		}
		else
		{
			integralDiff = 0;
		}

		//Calculates derivative error for forward/backward
		derivativeDiff = diffError - lastDiffError;
		lastDiffError = diffError;

		//Calculates voltage for forward/backward using PID constants
		powerDiff = kPDiff * diffError + kIDiff * integralDiff + kDDiff * derivativeDiff;

		//Calculates target voltage for each wheel using angle, distance, and strafe voltages
		double leftFrontSpeed = powerDistance + powerAngle + powerDiff;
		double leftBackSpeed = -powerDistance + powerAngle + powerDiff;
		double rightFrontSpeed = -powerDistance - powerAngle + powerDiff;
		double rightBackSpeed = powerDistance - powerAngle + powerDiff;

		//Limits voltage of each motor under threshold and scales accordingly
		double maxCurrSpeed = max(max(abs(leftFrontSpeed), abs(leftBackSpeed)), max(abs(rightFrontSpeed), abs(rightBackSpeed)));
		if (maxCurrSpeed > maxVel)
		{
			leftFrontSpeed = leftFrontSpeed * (maxVel / maxCurrSpeed);
			leftBackSpeed = leftBackSpeed * (maxVel / maxCurrSpeed);
			rightFrontSpeed = rightFrontSpeed * (maxVel / maxCurrSpeed);
			rightBackSpeed = rightBackSpeed * (maxVel / maxCurrSpeed);
		}

		//Supplies voltages to motors
		leftFrontMotor = leftFrontSpeed;
		leftBackMotor = leftBackSpeed;
		rightFrontMotor = rightFrontSpeed;
		rightBackMotor = rightBackSpeed;

		pros::delay(10);
	}

	//Stops motors at end of motion
	if (stopMotors)
	{
		leftFrontMotor = 0;
		leftBackMotor = 0;
		rightFrontMotor = 0;
		rightBackMotor = 0;
	}
}

/**
 * Strafes left using PID control
 * 
 * Parameters:
 * targetTheta: target heading for motion
 * distanceLine: list of points to generate ideal path
 * maxVel: max voltage supplied to motors
 * thresholdDistanceError: threshold distance error before stopping motion
 * kpAngle: proportional constant for angle
 * kPDistance: proportional constant for distance
 * kPDiff: proportional constant for forward/backward correction
 * kIAngle: integral constant for angle
 * kIDistance: integral constant for distance
 * kIDiff: integral constant for forward/backward correction
 * kDAngle: derivative constant for angle
 * kDDistance: derivative constant for distance
 * kDDiff: derivative constant for forward/backward correction
 * stopMotors: specifies whether to stop motors at end of motion
 */
void pidLeft(double targetTheta, vector<vector<double>> distanceLine, double maxVel, double thresholdDistanceError, double kPAngle, double kPDistance, double kPDiff, double kIAngle, double kIDistance, double kIDiff, double kDAngle, double kDDistance, double kDDiff, bool stopMotors)
{
	double distanceError = 99999999;
	double angleError = 99999;
	double diffError = 99999;
	double lastDistanceError = 0.0;
	double lastAngleError = 0.0;
	double lastDiffError = 0.0;
	double powerAngle = 0.0;
	double powerDistance = 0.0;
	double powerDiff = 0.0;
	double integralLimitAngle = 0.0;
	double integralLimitDistance = 0.0;
	double integralLimitDiff = 0.0;
	double integralAngle = 0.0;
	double integralDistance = 0.0;
	double integralDiff = 0.0;
	double derivativeAngle = 0.0;
	double derivativeDistance = 0.0;
	double derivativeDiff = 0.0;

	double m;

	//Calculates slope of target line
	if (distanceLine[0][0] == distanceLine[1][0])
	{
		m = WINT_MAX;
	}
	else
	{
		m = (distanceLine[0][1] - distanceLine[1][1]) / (distanceLine[0][0] - distanceLine[1][0]);
	}

	//Calculates equation of target line
	double tempB = distanceLine[0][1] - m * distanceLine[0][0];
	double a = -1 * m;
	double b = 1;
	double c = -tempB;

	//Rotates target line to face towards heading of 0
	double origTheta = atan(m);
	double p = -1 * c / sqrt(pow(a, 2) + pow(b, 2));
	double beta = M_PI / 2;
	double rotatedA = sin(beta);
	double rotatedB = cos(beta);
	double rotatedC = -1 * p;

	//Calculates end coordinates post-rotation
	double hypEndpoint = sqrt(pow((distanceLine[1][0]), 2) + pow((distanceLine[1][1]), 2));
	double rotatedEndX = distanceLine[1][0] * cos(beta - origTheta) - distanceLine[1][1] * sin(beta - origTheta);
	double rotatedEndY = distanceLine[1][0] * sin(beta - origTheta) + distanceLine[1][1] * cos(beta - origTheta);

	while (abs(distanceError) > thresholdDistanceError)
	{	
		//Gets robot's current coordinates and heading
		double currX = position.getPosition()[0];
		double currY = position.getPosition()[1];
		double currTheta = position.getTheta();
		
		//Calculates rotated coordinates and headings
		double adjThetaRobot = currTheta + beta - origTheta;
		double rotatedCurrX = currX * cos(beta - origTheta) - currY * sin(beta - origTheta);
		double rotatedCurrY = currX * sin(beta - origTheta) + currY * cos(beta - origTheta);

		//Calculates angle error
		angleError = calcAngleDiff(targetTheta, currTheta);

		//Calculates distance error from closest point on target line to endpoint
		distanceError = abs(rotatedEndY - rotatedCurrY);

		//Calculates forward/backward error from closest point on target line to endpoint
		diffError = rotatedEndX - rotatedCurrX;

		//Calculates integral error for angle
		if (kIAngle != 0)
		{
			if (abs(angleError) < integralLimitAngle)
			{
				integralAngle += angleError;
			}
			else
			{
				integralAngle = 0;
			}
		}
		else
		{
			integralAngle = 0;
		}

		//Calculates derivative error for angle
		derivativeAngle = angleError - lastAngleError;
		lastAngleError = angleError;

		//Calculates angle voltage using PID constants
		powerAngle = kPAngle * angleError + kIAngle * integralAngle + kDAngle * derivativeAngle;

		//Calculates integral error for distance
		if (kIDistance != 0)
		{
			if (abs(distanceError) < integralLimitDistance)
			{
				integralDistance += distanceError;
			}
			else
			{
				integralDistance = 0;
			}
		}
		else
		{
			integralDistance = 0;
		}

		//Calculates derivative error for distance
		derivativeDistance = distanceError - lastDistanceError;
		lastDistanceError = distanceError;

		//Calculates distance voltage using PID constants 
		powerDistance = kPDistance * distanceError + kIDistance * integralDistance + kDDistance * derivativeDistance;

		//Calculates integral error for forward/backward
		if (kIDiff != 0)
		{
			if (abs(diffError) < integralLimitDiff)
			{
				integralDiff += diffError;
			}
			else
			{
				integralDiff = 0;
			}
		}
		else
		{
			integralDiff = 0;
		}

		//Calculates derivative error for forward/backward
		derivativeDiff = diffError - lastDiffError;
		lastDiffError = diffError;

		//Calculates voltage for forward/backward using PID constants
		powerDiff = kPDiff * diffError + kIDiff * integralDiff + kDDiff * derivativeDiff;

		//Calculates target voltage for each wheel using angle, distance, and strafe voltages
		double leftFrontSpeed = -powerDistance + powerAngle + powerDiff;
		double leftBackSpeed = powerDistance + powerAngle + powerDiff;
		double rightFrontSpeed = powerDistance - powerAngle + powerDiff;
		double rightBackSpeed = -powerDistance - powerAngle + powerDiff;

		//Limits voltage of each motor under threshold and scales accordingly
		double maxCurrSpeed = max(max(abs(leftFrontSpeed), abs(leftBackSpeed)), max(abs(rightFrontSpeed), abs(rightBackSpeed)));
		if (maxCurrSpeed > maxVel)
		{
			leftFrontSpeed = leftFrontSpeed * (maxVel / maxCurrSpeed);
			leftBackSpeed = leftBackSpeed * (maxVel / maxCurrSpeed);
			rightFrontSpeed = rightFrontSpeed * (maxVel / maxCurrSpeed);
			rightBackSpeed = rightBackSpeed * (maxVel / maxCurrSpeed);
		}

		//Supplies voltages to motors
		leftFrontMotor = leftFrontSpeed;
		leftBackMotor = leftBackSpeed;
		rightFrontMotor = rightFrontSpeed;
		rightBackMotor = rightBackSpeed;

		pros::delay(10);
	}

	//Stops motors at end of motion
	if (stopMotors)
	{
		leftFrontMotor = 0;
		leftBackMotor = 0;
		rightFrontMotor = 0;
		rightBackMotor = 0;
	}
}