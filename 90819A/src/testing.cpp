 #define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <vector>
#include <cstdint>
#include <cstdio>

using namespace std;

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

 void pidForward(double targetX, double targetY, double targetTheta, vector<vector<double>> distanceLine, double maxVel, double thresholdDistanceError, double kPAngle, double kPDistance, double kPDiff, double kIAngle, double kIDistance, double kIDiff, double kDAngle, double kDDistance, double kDDiff, bool stopMotors)
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
	 if (distanceLine[0][0] == distanceLine[1][0]) {
		 m = WINT_MAX;
	 }
	 else {
		 m = (distanceLine[0][1] - distanceLine[1][1]) / (distanceLine[0][0] - distanceLine[1][0]);
	 }

	 //double m = tan((M_PI / 2) * ((int)(targetTheta / (M_PI / 2)) + 1) - targetTheta + (M_PI / 2) * ((int)(targetTheta / (M_PI / 2))));

	 double tempB = distanceLine[0][1] - m * distanceLine[0][0];
	 //double tempB = targetY - m * targetX;
	 double a = -1 * m;
	 double b = 1;
	 double c = -tempB;
	 double hyp1 = sqrt(pow((distanceLine[0][1]), 2) + pow((distanceLine[0][0]), 2));
	 double adjTheta1 = atan(distanceLine[0][1] / distanceLine[0][0]) + atan(m);
	 double hyp2 = sqrt(pow((distanceLine[1][1]), 2) + pow((distanceLine[1][0]), 2));
	 double adjTheta2 = atan(distanceLine[1][1] / distanceLine[1][0]) + atan(m);
	 double rotatedX1 = cos(adjTheta1) * hyp1;
	 double rotatedX2 = cos(adjTheta2) * hyp2;
	 double rotatedY1 = sin(adjTheta1) * hyp1;
	 double rotatedY2 = sin(adjTheta2) * hyp2;

	 printf("Line: %.3fx+%.3f\n", m, tempB);
	 printf("(%.3f, %.3f) and (%.3f, %.3f)\n", rotatedX1, rotatedY1, rotatedX2, rotatedY2);
	 printf("hyp1: %.3f", hyp1);
	 printf("adjTheta1: %.3f", adjTheta1);
	 printf("hyp2: %.3f", hyp2);
	 printf("adjTheta2: %.3f", adjTheta2);
	 //printf("rotatedY1: %.3f\n", rotatedY1);

	 double rotatedM;
	 if (distanceLine[0][0] == distanceLine[1][0]) {
		 rotatedM = WINT_MAX;
	 }
	 else {
		 rotatedM = (rotatedY1 - rotatedY2) / (rotatedX1 - rotatedX2);
	 }

	 //double m = tan((M_PI / 2) * ((int)(targetTheta / (M_PI / 2)) + 1) - targetTheta + (M_PI / 2) * ((int)(targetTheta / (M_PI / 2))));

	 double rotatedTempB = rotatedY1 - rotatedM * rotatedX1;



	 while (abs(distanceError) > thresholdDistanceError)
	 {
		 //printf("m: %.3f\n", m);
		 //printf("a: %.3f\n", a);
		 //printf("b: %.3f\n", b);
		 //printf("c: %.3f\n", c);

         double currX;
         double currY;
         double currTheta;
		 printf("Curr x: ");
         scanf("%lf", &currX);
         printf("Curr y: ");
         scanf("%lf", &currY);
         printf("Curr theta: ");
         scanf("%lf", &currTheta);

		 double hypRobot = sqrt(pow((currY), 2) + pow((currX), 2));
		 double adjThetaRobot = atan(currY / currX) + currTheta;
		 double rotatedCurrX = cos(adjThetaRobot) * hypRobot;
		 double rotatedCurrY = sin(adjThetaRobot) * hypRobot;

		 double perpA;
		 double perpB;
		 double perpC;
		 double mPerp = -1 / m;

		 //double x;
		 //double y;

		 //if (abs(mPerp) < 9999) {

		 //	// Ax + By + C = 0
		 //	// (y-currY) = mPerp(x-currX)

		 //	perpA = -mPerp;
		 //	perpB = 1;
		 //	perpC = mPerp * currX - currY;

		 //	x = (perpC - c) / (a - perpA);
		 //	y = mPerp * (x - currX) + currY;
		 //}

		 //else {
		 //	perpA = 1;
		 //	perpB = 0;
		 //	perpC = -currX;
		 //	x = currX;
		 //	y = -c;
		 //}




		 //printf("(%.3f, %.3f, %.3f)", perpA, perpB, perpC);
		 //printf("(%.3f, %.3f)", x, y);

		 //distanceError = sqrt(pow(targetX - x, 2) + pow(targetY - y, 2) * 1.0);
		 angleError = calcAngleDiff(targetTheta, currTheta);

		 //diffError = (a * currX + b * currY + c) / sqrt(pow(a, 2) + pow(b, 2));

		 distanceError = sqrt(pow(rotatedX1 - rotatedX2, 2) + pow(rotatedY1 - rotatedY2, 2));
		 diffError = rotatedX1 - rotatedCurrX;

		 if (adjThetaRobot > M_PI / 2 && adjThetaRobot < M_PI * 3 / 2)
		 {
			 diffError *= -1;
		 }

		 if (kDDiff == 1) {
			 diffError *= -1;
		 }

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

		 derivativeAngle = angleError - lastAngleError;
		 lastAngleError = angleError;

		 powerAngle = kPAngle * angleError + kIAngle * integralAngle + kDAngle * derivativeAngle;

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

		 derivativeDistance = distanceError - lastDistanceError;
		 lastDistanceError = distanceError;

		 powerDistance = kPDistance * distanceError + kIDistance * integralDistance + kDDistance * derivativeDistance;

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

		 derivativeDiff = diffError - lastDiffError;
		 lastDiffError = diffError;

		 // powerDiff = kPDiff * diffError + kIDiff * integralDiff + kDDiff * derivativeDiff;
		 powerDiff = kPDiff * diffError;
		 //printf("Angle Power: %.3f", powerAngle);


		 double leftFrontSpeed = powerDistance + powerAngle + powerDiff;
		 double leftBackSpeed = powerDistance + powerAngle - powerDiff;
		 double rightFrontSpeed = powerDistance - powerAngle - powerDiff;
		 double rightBackSpeed = powerDistance - powerAngle + powerDiff;


		 double maxCurrSpeed = max(max(abs(leftFrontSpeed), abs(leftBackSpeed)), max(abs(rightFrontSpeed), abs(rightBackSpeed)));

		 if (maxCurrSpeed > maxVel) {
			 //leftFrontSpeed = leftFrontSpeed * (maxVel / maxCurrSpeed);
			 //leftBackSpeed = leftBackSpeed * (maxVel / maxCurrSpeed);
			 //rightFrontSpeed = rightFrontSpeed * (maxVel / maxCurrSpeed);
			 //rightBackSpeed = rightBackSpeed * (maxVel / maxCurrSpeed);
		 }


		 //printf("Current Position: (%.3f, %.3f, %.3f)\n", currX, currY, currTheta);
		 //printf("Distance Error: %.3f\n", distanceError);
		 //printf("Angle Error: %.3f\n", angleError);
		 //printf("Diff Error: %.3f\n\n", diffError);

		 //printf("leftFront: %.3f\n", leftFrontSpeed);
		 //printf("leftBack: %.3f\n", leftBackSpeed);
		 //printf("rightFront: %.3f\n", rightFrontSpeed);
		 //printf("rightBack: %.3f\n\n\n", rightBackSpeed);

		 //leftFrontMotor = leftFrontSpeed;
		 //leftBackMotor = leftBackSpeed;
		 //rightFrontMotor = rightFrontSpeed;
		 //rightBackMotor = rightBackSpeed;

		 //pros::delay(10);
	 }

	 if (stopMotors)
	 {
		 //leftFrontMotor = 0;
		 //leftBackMotor = 0;
		 //rightFrontMotor = 0;
		 //rightBackMotor = 0;
	 }
 }

 int main()
 {
	 pidForward(5, 24, 0, { {0,0},{5,5} }, 63, 0.5, 50, 50, 20, 0, 0, 0, 0, 0, 0, true);
     //pidBackward(-10, 0, M_PI, 127, 0.5, 20, 20, 20, 0, 0, 0, 0, 0, 0, false);
 }