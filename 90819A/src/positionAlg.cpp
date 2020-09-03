#include "positionAlg.h"

double WHEEL_DIAMETER = 2.75;
double DISTANCE_TO_LEFT_ENCODER = 6.75;
double DISTANCE_TO_RIGHT_ENCODER = 6.75;
double DISTANCE_TO_BACK_ENCODER = 2.75;

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

double x;
double y;
double r;
double theta;
double newX;
double newY;
double thetaM;

int count2 = 0;

double PositionAlg::getTheta()
{
    return theta;
}

vector<double> PositionAlg::getPosition()
{
    return positionVector;
}

void PositionAlg::calcPosition(void *ignore)
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

    leftEncoderDistance = leftEncoderDegreesDifference * M_PI / 180.0 * WHEEL_DIAMETER / 2;
    rightEncoderDistance = rightEncoderDegreesDifference * M_PI / 180.0 * WHEEL_DIAMETER / 2;
    backEncoderDistance = backEncoderDegreesDifference * M_PI / 180.0 * WHEEL_DIAMETER / 2;

    // printf("Left: %.3f\n", leftEncoderDistance);
    // printf("right: %.3f\n", rightEncoderDistance);
    // printf("Back: %.3f\n", backEncoderDegrees * M_PI / 180.0 * WHEEL_DIAMETER/2);

    deltaTheta = (leftEncoderDistance - rightEncoderDistance) / (DISTANCE_TO_LEFT_ENCODER + DISTANCE_TO_RIGHT_ENCODER);

    theta += deltaTheta;

    if (deltaTheta != 0)
    {
        x = 2 * sin(deltaTheta / 2) * (backEncoderDistance / deltaTheta + DISTANCE_TO_BACK_ENCODER);
        y = 2 * sin(deltaTheta / 2) * (rightEncoderDistance / deltaTheta + DISTANCE_TO_RIGHT_ENCODER);
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

    //convert to polar, rotate by negative theta, convert back

    thetaM = theta + deltaTheta / 2;
    
    newX = x * cos(-thetaM) - y * sin(-thetaM);
    newY = y * cos(-thetaM) + x * sin(-thetaM);

    positionVector[0] = positionVector[0] + newX;
    positionVector[1] = positionVector[1] + newY;

    //printf("x-coordinate: %.3f\n", positionVector[0]);
    //printf("y-coordinate: %.3f\n", positionVector[1]);

    //printf("change in raw x: %.3f\n", x);
    //printf("change in raw y: %.3f\n", y);
    // printf("change in x: %.3f\n", newX);
    // printf("change in y: %.3f\n", newY);
    // printf("x: %.3f\n", positionVector[0]);
    // printf("y: %.3f\n", positionVector[1]);
    // printf("theta: %.3f\n", theta);


    // pros::delay(10000);
    // runPositionTask();
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

