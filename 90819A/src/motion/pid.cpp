#include "motion/pid.h"

double calcAngleDiff(double angle1, double angle2){
	double num1 = angle1 - angle2;
    double num2 = (angle1 - 2 * M_PI) - angle2;
    double num3 = angle1 - (angle2 - 2 * M_PI);
    if(abs(num1) < abs(num2) && abs(num1) < abs(num3)){
        return num1;
	} else if(abs(num2) < abs(num1) && abs(num2) < abs(num3)){
        return num2;
	} else{
		return num3;
	}
}

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
        //calcPosition();
        printf("theta: %.3f\n", position.getTheta() * 180.0 / M_PI);

        error = calcAngleDiff(target, position.getTheta());

        if (kI != 0)
        {
            if (abs(error) < integralLimit)
                integral += error;
            else
                integral = 0;
        }
        else
            integral = 0;

        derivative = error - lastError;
        lastError = error;

        power = kP * error + kI * integral + kD * derivative;

        if (power > maxVel)
            power = maxVel;
        if (power < -maxVel)
            power = -maxVel;

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

void pidForward(double targetX, double targetY, double targetTheta, double maxVel, double thresholdDistanceError, double kP, double kPStraight)
{   
    double distanceError = 99999999;
    double angleError = 99999;
    double power;
    double angleCorrection;


    while (abs(distanceError) > thresholdDistanceError){
        //calcPosition();
        printf("getTheta(): %.3f\n", position.getTheta() * 180.0 / M_PI);
        printf("x: %.3f\n", position.getPosition()[0]);
        printf("y: %.3f\n", position.getPosition()[1]);
        printf("targetX: %.3f\n", targetX);
        printf("targetY: %.3f\n", targetY);


        distanceError = abs(targetX - position.getPosition()[0]);
        // distanceError = sqrt(pow(targetX - position.getPosition()[0], 2) + pow(targetY - position.getPosition()[1], 2) * 1.0);
        angleError = calcAngleDiff(targetTheta, position.getTheta());
        
        printf("Distance Error: %.3f", distanceError);
        power = kP * distanceError;
        angleCorrection = kPStraight * angleError;

        if (angleCorrection > 60)
            angleCorrection = 60;
        if (angleCorrection < -60)
            angleCorrection = -60;

        printf("power: %.3f\n", power);
        printf("angleCorrection: %.3f\n", angleCorrection);

        if (power > maxVel)
            power = maxVel;
        if (power < -maxVel)
            power = -maxVel;

        leftFrontMotor = power + angleCorrection;
        leftBackMotor = power + angleCorrection;
        rightFrontMotor = power - angleCorrection;
        rightBackMotor = power - angleCorrection;

        
     }

     leftFrontMotor = 0;
     leftBackMotor = 0;
     rightFrontMotor = 0;
     rightBackMotor = 0;
}