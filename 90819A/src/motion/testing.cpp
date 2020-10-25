// #include <cstdio>
// #define _USE_MATH_DEFINES
// #include <math.h>
// #include <algorithm>
// #include <vector>

// // double calcAngleDiff(double angle1, double angle2)
// {
//     double num1 = angle1 - angle2;
//     double num2 = (angle1 - 2 * M_PI) - angle2;
//     double num3 = angle1 - (angle2 - 2 * M_PI);
//     if (abs(num1) < abs(num2) && abs(num1) < abs(num3))
//     {
//         return num1;
//     }
//     else if (abs(num2) < abs(num1) && abs(num2) < abs(num3))
//     {
//         return num2;
//     }
//     else
//     {
//         return num3;
//     }
// }

// void pidForwardBeta(double targetX, double targetY, double targetTheta, double maxVel, double thresholdDistanceError, double kPAngle, double kPDistance, double kPDiff, double kIAngle, double kIDistance, double kIDiff, double kDAngle, double kDDistance, double kDDiff)
// {
//     double distanceError = 99999999;
//     double angleError = 99999;
//     double diffError = 99999;
//     double lastDistanceError = 0.0;
//     double lastAngleError = 0.0;
//     double lastDiffError = 0.0;
//     double powerAngle = 0.0;
//     double powerDistance = 0.0;
//     double powerDiff = 0.0;
//     double integralLimitAngle = 0.0;
//     double integralLimitDistance = 0.0;
//     double integralLimitDiff = 0.0;
//     double integralAngle = 0.0;
//     double integralDistance = 0.0;
//     double integralDiff = 0.0;
//     double derivativeAngle = 0.0;
//     double derivativeDistance = 0.0;
//     double derivativeDiff = 0.0;

//     double m = tan((M_PI/2)*((int)(targetTheta / (M_PI/2)) + 1) - targetTheta + (M_PI/2)*((int)(targetTheta / (M_PI/2))));

//     double tempB = targetY - m * targetX;
//     double a = -1 * m;
//     double b = 1;
//     double c = -tempB;

//     printf("m: %.3f\n", m);
//     printf("a: %.3f\n", a);
//     printf("b: %.3f\n", b);
//     printf("c: %.3f\n", c);

//     while (abs(distanceError) > thresholdDistanceError)
//     {
//         double currX;
//         double currY;
//         double currTheta;

//         printf("Curr x: ");
//         scanf("%lf", &currX);
//         printf("Curr y: ");
//         scanf("%lf", &currY);
//         printf("Curr theta: ");
//         scanf("%lf", &currTheta);

//         // double currX = positionX;
//         // double currY = positionY;
//         // double currTheta = theta;
//         distanceError = sqrt(pow(targetX - currX, 2) + pow(targetY - currY, 2) * 1.0);
//         angleError = calcAngleDiff(targetTheta, currTheta);

//         diffError = (a * currX + b * currY + c) / sqrt(pow(a, 2) + pow(b, 2));

//         if (kIAngle != 0)
//         {
//             if (abs(angleError) < integralLimitAngle)
//             {
//                 integralAngle += angleError;
//             }
//             else
//             {
//                 integralAngle = 0;
//             }
//         }
//         else
//         {
//             integralAngle = 0;
//         }

//         derivativeAngle = angleError - lastAngleError;
//         lastAngleError = angleError;

//         powerAngle = kPAngle * angleError + kIAngle * integralAngle + kDAngle * derivativeAngle;

//         if (kIDistance != 0)
//         {
//             if (abs(distanceError) < integralLimitDistance)
//             {
//                 integralDistance += distanceError;
//             }
//             else
//             {
//                 integralDistance = 0;
//             }
//         }
//         else
//         {
//             integralDistance = 0;
//         }

//         derivativeDistance = distanceError - lastDistanceError;
//         lastDistanceError = distanceError;

//         powerDistance = kPDistance * distanceError + kIDistance * integralDistance + kDDistance * derivativeDistance;

//         if (kIDiff != 0)
//         {
//             if (abs(diffError) < integralLimitDiff)
//             {
//                 integralDiff += diffError;
//             }
//             else
//             {
//                 integralDiff = 0;
//             }
//         }
//         else
//         {
//             integralDiff = 0;
//         }

//         derivativeDiff = diffError - lastDiffError;
//         lastDiffError = diffError;

//         powerDiff = kPDiff * diffError + kIDiff * integralDiff + kDDiff * derivativeDiff;

//         double leftFrontSpeed = powerDistance + powerAngle + powerDiff;
//         double leftBackSpeed = powerDistance + powerAngle - powerDiff;
//         double rightFrontSpeed = powerDistance - powerAngle - powerDiff;
//         double rightBackSpeed = powerDistance - powerAngle + powerDiff;
//         double maxCurrSpeed = std::max(std::max(abs(leftFrontSpeed), abs(leftBackSpeed)), std::max(abs(rightFrontSpeed), abs(rightBackSpeed)));
        


//         if (maxCurrSpeed > 127) {
//         	leftFrontSpeed = leftFrontSpeed * (127 / maxCurrSpeed);
//         	leftBackSpeed = leftBackSpeed * (127 / maxCurrSpeed);
//         	rightFrontSpeed = rightFrontSpeed * (127 / maxCurrSpeed);
//         	rightBackSpeed = rightBackSpeed * (127 / maxCurrSpeed);
//         }

//         printf("leftFront: %.3f\n", leftFrontSpeed);
//         printf("leftBack: %.3f\n", leftBackSpeed);
//         printf("rightFront: %.3f\n", rightFrontSpeed);
//         printf("rightBack: %.3f\n", rightBackSpeed);
//         printf("Current Position: (%.3f, %.3f, %.3f)\n", currX, currY, currTheta);
//         printf("Distance Error: %.3f\n", distanceError);
//         printf("Angle Error: %.3f\n", angleError);
//         printf("Diff Error: %.3f\n", diffError);

//         // leftFrontMotor = leftFrontSpeed;
//         // leftBackMotor = leftBackSpeed;
//         // rightFrontMotor = rightFrontSpeed;
//         // rightBackMotor = rightBackSpeed;
//         // pros::delay(10);
//     }

//     // leftFrontMotor = 0;
//     // leftBackMotor = 0;
//     // rightFrontMotor = 0;
//     // rightBackMotor = 0;
// }

// int main()
// {
//     pidForwardBeta(0, 10, 0, 127, 0.5, 20, 20, 20, 0, 0, 0, 0, 0, 0);
// }