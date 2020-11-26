#include "motion/purePursuit.h"

using namespace std;
time_t currentTime;
double WHEEL_DIAMETER2 = 2.75;

//these are the reccomended ways to create the task
// pros::Task positionController(bind(&PositionAlg::calcPosition, &position));
// pros::Task positionController([&](){position.calcPosition();});

PositionAlg position;
pros::Task positionController(position.calcPosition, NULL, "Position Tracker");

Indexing indexer;
pros::Task indexController(indexer.indexingTask, NULL, "Ball Tracker");

vector<vector<double>> generateLinearPath(double initX, double initY, double finalX, double finalY, double spacing)
{
    //spacing is in inches between points
    vector<vector<double>> pointsList = {{0.0}};
    pointsList = {};
    vector<double> changeVector = {finalX - initX, finalY - initY};
    double magnitude = sqrt(pow(changeVector[0], 2) + pow(changeVector[1], 2));
    double numPoints = ceil(magnitude / spacing);
    changeVector[0] = changeVector[0] * spacing / magnitude;
    changeVector[1] = changeVector[1] * spacing / magnitude;
    for (int i = 0; i < numPoints; i++)
    {
        vector<double> newVector = {initX + changeVector[0] * i, initY + changeVector[1] * i};
        pointsList.push_back(newVector);
    }
    vector<double> finalVector{finalX, finalY};
    pointsList.push_back(finalVector);
    return pointsList;
}

vector<double> calculateDistance(vector<vector<double>> pointsList)
{
    vector<double> distanceList = {0.0};
    distanceList = {};
    distanceList.push_back(0.0);
    for (int i = 1; i < pointsList.size(); i++)
    {
        distanceList.push_back(distanceList[i - 1] + sqrt(pow((pointsList[i][0] - pointsList[i - 1][0]), 2) + pow((pointsList[i][1] - pointsList[i - 1][1]), 2)));
    }
    return distanceList;
}

vector<double> calculateCurve(vector<vector<double>> pointsList)
{
    vector<double> curveList = {0.0};
    curveList = {};
    curveList.push_back(0.0);
    for (int i = 1; i < pointsList.size() - 1; i++)
    {
        double x1 = pointsList[i][0];
        double x2 = pointsList[i - 1][0];
        if (x1 == x2)
        {
            x1 += 0.001;
        }
        double x3 = pointsList[i + 1][0];
        double y1 = pointsList[i][1];
        double y2 = pointsList[i - 1][1];
        double y3 = pointsList[i + 1][1];
        double k1 = 0.5 * (pow(x1, 2) + pow(y1, 2) - pow(x2, 2) - pow(y2, 2)) / (x1 - x2);
        double k2 = (y1 - y2) / (x1 - x2);
        double b = 0.5 * (pow(x2, 2) - 2 * x2 * k1 + pow(y2, 2) - pow(x3, 2) + 2 * x3 * k1 - pow(y3, 2)) / (x3 * k2 - y3 + y2 - x2 * k2);
        double a = k1 - k2 * b;
        curveList.push_back(1 / sqrt(pow(x1 - a, 2) + pow(y1 - b, 2)));
    }
    curveList.push_back(0.0);
    return curveList;
}

vector<vector<double>> smooth(vector<vector<double>> pointsList, double a, double b, double tolerance)
{
    //b should be a value between 0.75 and 0.98
    vector<vector<double>> newPointsList = pointsList;
    double change = tolerance;
    while (change >= tolerance)
    {
        change = 0.0;
        for (int i = 1; i < pointsList.size() - 1; i++)
        {
            for (int j = 0; j < pointsList[i].size(); j++)
            {
                double aux = newPointsList[i][j];
                newPointsList[i][j] += a * (pointsList[i][j] - newPointsList[i][j]) + b * (newPointsList[i - 1][j] + newPointsList[i + 1][j] - (2.0 * newPointsList[i][j]));
                change += abs(aux - newPointsList[i][j]);
            }
        }
    }
    return newPointsList;
}

vector<double> calculateVelocity(vector<vector<double>> pointsList, vector<double> curveList, double maxVelocity, double maxAccel, double turnConstant)
{
    //turnConstant should be between 1.0 and 5.0
    vector<double> maxVelList = {0.0};
    maxVelList = {};
    for (int i = 0; i < curveList.size(); i++)
    {
        if (curveList[i] == 0.0)
        {
            curveList[i] = 0.001;
        }
        maxVelList.push_back(min(maxVelocity, (turnConstant / curveList[i])));
    }

    vector<double> targetVelList = {0};
    targetVelList = {};
    targetVelList.push_back(0.0);
    double prevVel = 0.0;
    for (int i = 1; i < maxVelList.size(); i++)
    {
        prevVel = sqrt(pow(prevVel, 2) + 2 * maxAccel * 0.0254 * sqrt(pow((pointsList[i][0] - pointsList[i - 1][0]), 2) + pow((pointsList[i][1] - pointsList[i - 1][1]), 2)));
        // this might be casuing problems if we curve
        if (prevVel > maxVelList[i])
        {
            prevVel = maxVelList[i];
        }
        targetVelList.push_back(prevVel);
    }

    vector<double> velList(maxVelList.size(), 0.0);
    double previousVel = 0.0;
    for (int i = maxVelList.size() - 2; i >= 0; i--)
    {
        double distance = sqrt(pow((pointsList[i + 1][0] - pointsList[i][0]), 2) + pow((pointsList[i + 1][1] - pointsList[i][1]), 2));
        distance = distance * 0.0254;
        previousVel = min(targetVelList[i], sqrt(pow(previousVel, 2) + 2 * maxAccel * distance));
        velList[i] = previousVel;
    }

    //for (int i = 0; i < targetVelList.size(); i++) {
    //  printf("targetVelList #%d: %.3f\n", i, targetVelList[i]);
    //}

    return velList;
}

double dot(vector<double> a, vector<double> b)
{
    return a[0] * b[0] + a[1] * b[1];
}

vector<double> findLookAheadPoint(double x, double y, vector<vector<double>> pointsList, int closestPoint, int lookAheadPointsNum, double spacing)
{

    //printf("closestPoint: %d\n", closestPoint);

    vector<double> E = pointsList[closestPoint];
    vector<double> L = pointsList[closestPoint + lookAheadPointsNum];
    vector<double> C = {x, y};
    vector<double> d = {L[0] - E[0], L[1] - E[1]};
    vector<double> f = {E[0] - C[0], E[1] - C[1]};

    double r = spacing * lookAheadPointsNum;
    double a = dot(d, d);
    double b = 2 * dot(f, d);
    double c = dot(f, f) - r * r;
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
    {
        //no intersection
        if (closestPoint != pointsList.size() - lookAheadPointsNum - 1)
        {
            return findLookAheadPoint(x, y, pointsList, closestPoint, lookAheadPointsNum + 1, spacing);
        }
        else
        {
            return pointsList[pointsList.size() - 1];
        }
    }
    else
    {
        double t1 = (-b - sqrt(discriminant)) / (2 * a);
        double t2 = (-b + sqrt(discriminant)) / (2 * a);
        if (t1 >= 0 && t1 <= 1)
        {
            return {E[0] + t1 * d[0], E[1] + t1 * d[1]};
        }
        else if (t2 >= 0 && t2 <= 1)
        {
            return {E[0] + t2 * d[0], E[1] + t2 * d[1]};
        }
        else
        {
            if (closestPoint != pointsList.size() - lookAheadPointsNum - 1)
            {
                return findLookAheadPoint(x, y, pointsList, closestPoint, lookAheadPointsNum + 1, spacing);
            }
            else
            {
                return pointsList[pointsList.size() - 1];
            }
        }
    }
}

double findCurvature(vector<double> lookAheadPoint, double Rx, double Ry, double kC)
{
    double angle = (M_PI / 2 - position.getTheta());

    double a = -1 * tan(angle);
    double c = tan(angle) * Rx - Ry;
    double x = abs(a * lookAheadPoint[0] + lookAheadPoint[1] + c) / sqrt(pow(a, 2) + 1);
    double side = (sin(angle) * (lookAheadPoint[0] - Rx) - cos(angle) * (lookAheadPoint[1] - Ry)) / abs(sin(angle) * (lookAheadPoint[0] - Rx) - cos(angle) * (lookAheadPoint[1] - Ry));
    double curvature = (2 * x) / (pow((lookAheadPoint[0] - Rx), 2) + pow((lookAheadPoint[1] - Ry), 2));
    return curvature * side * kC;
}

double findCurvatureBackwards(vector<double> lookAheadPoint, double Rx, double Ry, double kC)
{
    double angle = int(M_PI / 2 - position.getTheta() + 180) % 360;
    double a = -1 * tan(angle);
    double c = tan(angle) * Rx - Ry;
    double x = abs(a * lookAheadPoint[0] + lookAheadPoint[1] + c) / sqrt(pow(a, 2) + 1);
    double side = (sin(angle) * (lookAheadPoint[0] - Rx) - cos(angle) * (lookAheadPoint[1] - Ry)) / abs(sin(angle) * (lookAheadPoint[0] - Rx) - cos(angle) * (lookAheadPoint[1] - Ry));
    double curvature = (2 * x) / (pow((lookAheadPoint[0] - Rx), 2) + pow((lookAheadPoint[1] - Ry), 2));
    return curvature * side * kC;
}

double findCurvatureLeft(vector<double> lookAheadPoint, double Rx, double Ry, double kC)
{
    // need to check angle
    double angle = int(M_PI / 2 - position.getTheta() + 270) % 360;
    double a = -1 * tan(angle);
    double c = tan(angle) * Rx - Ry;
    double x = abs(a * lookAheadPoint[0] + lookAheadPoint[1] + c) / sqrt(pow(a, 2) + 1);
    double side = (sin(angle) * (lookAheadPoint[0] - Rx) - cos(angle) * (lookAheadPoint[1] - Ry)) / abs(sin(angle) * (lookAheadPoint[0] - Rx) - cos(angle) * (lookAheadPoint[1] - Ry));
    double curvature = (2 * x) / (pow((lookAheadPoint[0] - Rx), 2) + pow((lookAheadPoint[1] - Ry), 2));
    return curvature * side * kC;
}

double findCurvatureRight(vector<double> lookAheadPoint, double Rx, double Ry, double kC)
{
    // need to check angle
    double angle = int(M_PI / 2 - position.getTheta() + 90) % 360;
    double a = -1 * tan(angle);
    double c = tan(angle) * Rx - Ry;
    double x = abs(a * lookAheadPoint[0] + lookAheadPoint[1] + c) / sqrt(pow(a, 2) + 1);
    double side = (sin(angle) * (lookAheadPoint[0] - Rx) - cos(angle) * (lookAheadPoint[1] - Ry)) / abs(sin(angle) * (lookAheadPoint[0] - Rx) - cos(angle) * (lookAheadPoint[1] - Ry));
    double curvature = (2 * x) / (pow((lookAheadPoint[0] - Rx), 2) + pow((lookAheadPoint[1] - Ry), 2));
    return curvature * side * kC;
}

vector<double> rateLimit(double velocity, double maxAccel, double prevVel)
{
    //velocity is target velocity
    //prevVal = current actual velocity
    double maxChange = 0.01 * maxAccel;
    double newVel = prevVel;
    double accel;

    //newVel > target
    //velocity - newVel

    if (-1 * maxChange > (velocity - newVel))
    {
        newVel += -1 * maxChange;
        accel = -1 * maxChange;
        printf(".Decelerate\n");
    }
    else if (maxChange < (velocity - newVel))
    {
        newVel += maxChange;
        accel = maxChange;
        printf(".Accelerate\n");
    }
    else
    {
        newVel += (velocity - newVel);
        accel = velocity - newVel;
    }
    currentTime = time(0);

    printf("%.3f,", velocity);
    printf("%.3f,", newVel);

    return {newVel, accel};
}

double convertToRPM(double value)
{
    return value / (2 * M_PI * WHEEL_DIAMETER2 * 2.54) * (100 * 2 * 60.0);
}

double convertToRPM(int value)
{
    return value / (2 * M_PI * WHEEL_DIAMETER2 * 2.54) * (100 * 2 * 60.0);
}

double convertToMeters(double value)
{
    return value * (2 * M_PI * WHEEL_DIAMETER2 * 2.54) / (100 * 2 * 60.0);
}

double convertToMeters(int value)
{

    return value * (2 * M_PI * WHEEL_DIAMETER2 * 2.54) / (100 * 2 * 60.0);
}

vector<double> findVelocities(double curvature, double trackWidth, double velocity, double maxAccel, double prevVel)
{
    vector<double> vel = rateLimit(velocity, maxAccel, prevVel);
    //vector<double> leftVel = rateLimit(velocity, maxAccel, prevVel[0]);
    //vector<double> rightVel = rateLimit(velocity, maxAccel, prevVel[1]);

    //printf("velocity: %.3f m/s\n", vel[0]);
    //printf("rpm: %.3f rpm\n", convertToRPM(vel[0]));

    //printf("leftVel: %.4f\n", leftVel[0]);
    //printf("rightVel: %.4f\n", rightVel[0]);s

    //printf("L: %.3f\n", vel[0] * (2 + curvature * trackWidth) / 2);
    //printf("R: %.3f\n", vel[0] * (2 - curvature * trackWidth) / 2);

    printf("%.3f\n", curvature);
    return {vel[0] * (2 + curvature * trackWidth) / 2, vel[0] * (2 - curvature * trackWidth) / 2, vel[0], vel[1]};
}

void ppMoveForward(vector<vector<double>> initPoints, double spacing, double smoothVal1, double smoothVal2, double smoothTolerance, double maxVelocity, double maxAccel, double turnConstant, int lookAheadPointsNum, double trackWidth, double Kv, double Ka, double Kp, double Kc)
{
    //initPoints are all the points in the motion, including start and end
    //spacing is in inches between points
    //smoothVal1 should be 1-smoothVal2
    //smoothVal2 should be a value between 0.75 and 0.98
    //maxVelocity is the highest speed the robot is allowed to reach during this movement
    //maxAccel is the highest acceleration the robot is allowed to encounter during this movement
    //turnConstant should be between 1.0 and 5.0
    //lookAheadPointsNum is the number of points to look ahead
    //smoothTolerance default is 0.001
    /*trackWidth is measured from the robot. Due to turning scrub,
     *you want to use a track width a few inches larger than the real one.*/
    /*start Kv at 1/maxVelocity and start all other constants at 0
      *Tune Kv until the velocities match up
      *Set Ka to 0.002
      *Tune until accelerating and decelerating velocities are near accurate
      *Start Kp at 0.01 and increase number to make more accurate
      *Setting Kp too high will result in a jittery motion*/
    //Kc is curvature constant
    int counter = 0;
    //calcPosition();
    vector<vector<double>> pointsList = {{0.0}};
    pointsList = {};
    if (initPoints.size() == 0)
    {
        return;
    }
    else if (initPoints.size() == 1)
    {
        pointsList = generateLinearPath(position.getPosition()[0], position.getPosition()[1], initPoints[0][0], initPoints[0][1], spacing);
    }
    else
    {
        pointsList = generateLinearPath(initPoints[0][0], initPoints[0][1], initPoints[1][0], initPoints[1][1], spacing);
        if (initPoints.size() > 2)
        {
            for (int i = 1; i < initPoints.size() - 1; i++)
            {
                vector<vector<double>> pointsList2 = generateLinearPath(initPoints[i][0], initPoints[i][1], initPoints[i + 1][0], initPoints[i + 1][1], spacing);
                pointsList.insert(pointsList.end(), pointsList2.begin(), pointsList2.end());
            }
            pointsList = smooth(pointsList, smoothVal1, smoothVal2, smoothTolerance);
        }
    }

    //vector <double> distanceList = calculateDistance(pointsList);
    vector<double> curveList = calculateCurve(pointsList);
    vector<double> velList = calculateVelocity(pointsList, curveList, maxVelocity, maxAccel, turnConstant);
    for (int i = 0; i < pointsList.size(); i++)
    {
        printf(".velList #%d: %.3f\n", i, velList[i]);
    }
    //for (int i = 0; i < curveList.size(); i++) {
    //  printf("curveList #%d: %.3f\n", i, curveList[i]);
    //}
    int closestPoint = 1;
    vector<double> velocities = {0.0, 0.0};
    currentTime = time(0);
    while (true)
    {
        printf(".Time: %.d", counter);
        //calcPosition();
        double x = position.getPosition()[0];
        double y = position.getPosition()[1];
        printf(".Location: (%.3f, %.3f, %.3f)\n", x, y, position.getTheta() * 180 / M_PI);
        vector<double> lookAheadPoint = {0.0};
        lookAheadPoint = {};
        double smallestDistance = sqrt(pow((pointsList[closestPoint][0] - x), 2) + pow((pointsList[closestPoint][1] - y), 2));
        for (int i = closestPoint + 1; i < pointsList.size(); i++)
        {
            double newDistance = sqrt(pow((pointsList[i][0] - x), 2) + pow((pointsList[i][1] - y), 2));
            if (smallestDistance > newDistance)
            {
                smallestDistance = newDistance;
                closestPoint = i;
            }
        }
        if (closestPoint < pointsList.size() - 1 - lookAheadPointsNum)
        {
            lookAheadPoint = findLookAheadPoint(x, y, pointsList, closestPoint, lookAheadPointsNum, spacing);
        }
        else
        {
            lookAheadPoint = pointsList[pointsList.size() - 1];
        }
        printf(".lookAheadPoint: (%.3f, %.3f)\n", lookAheadPoint[0], lookAheadPoint[1]);
        //might need to be distance for tolerance
        if (lookAheadPoint[0] == pointsList[pointsList.size() - 1][0] && lookAheadPoint[1] == pointsList[pointsList.size() - 1][1] && (closestPoint == pointsList.size() - 1))
        {
            printf(".here");
            break;
        }
        //printf("closestPoint: (%.3f,%.3f)\n", pointsList[closestPoint][0], pointsList[closestPoint][1]);

        double curvature = findCurvature(lookAheadPoint, x, y, Kc);
        //printf("Curvature: %.3f\n", curvature);
        //printf("curvature: %.3f\n", curvature);

        //Left wheel speed, right wheel speed, target velocity, accel
        velocities = findVelocities(curvature, trackWidth, velList[closestPoint], maxAccel, velocities[2]);
        //printf("velocities: (%.3f, %.3f)\n m/s", velocities[0], velocities[1]);

        double leftFF = Kv * velocities[0] + Ka * (velocities[3]);
        double rightFF = Kv * velocities[1] + Ka * (velocities[3]);
        double leftFB = Kp * (velocities[0] - (convertToMeters(leftFrontMotor.get_actual_velocity() + leftBackMotor.get_actual_velocity()) / 2.0));
        double rightFB = Kp * (velocities[1] - (convertToMeters(rightFrontMotor.get_actual_velocity() + rightBackMotor.get_actual_velocity()) / 2.0));

        //printf("Left FF: %.3f\n", (leftFF ));
        //printf("Left FB: %.3f\n", (leftFB));
        //printf("Right FF: %.3f\n", (rightFF));
        //printf("Right FB: %.3f\n", (rightFB));

        //printf("Motor Voltage (L): %.3f\n", convertToRPM(leftFF + leftFB) * 127.0 / 200.0);
        //printf("Motor Voltage (R): %.3f\n\n", convertToRPM(rightFF + rightFB) * 127.0 / 200.0);

        printf("%.3f,%.3f,%.3f,%.3f,%.3f\n", velocities[0], velocities[1], convertToMeters((leftFrontMotor.get_actual_velocity() + leftBackMotor.get_actual_velocity()) / 2), convertToMeters((rightFrontMotor.get_actual_velocity() + rightBackMotor.get_actual_velocity()) / 2), closestPoint * 1.0);

        leftFrontMotor = convertToRPM(leftFF + leftFB) * 127.0 / 200;
        leftBackMotor = convertToRPM(leftFF + leftFB) * 127.0 / 200;
        rightFrontMotor = convertToRPM(rightFF + rightFB) * 127.0 / 200;
        rightBackMotor = convertToRPM(rightFF + rightFB) * 127.0 / 200;

        //printf("Left speed: %.3f m/s\n", leftFrontMotor.get_actual_velocity() * 100 / (2 * M_PI * 4.0 * 2.54 * 60);
        //printf("Right speed: %.3f m/s\n", rightFrontMotor.get_actual_velocitty() * 100 / (2 * M_PI * 4.0 * 2.54 * 60));

        //printf("leftSpeed: %.4f\n", (leftFF + leftFB));
        //printf("rightSpeed: %.4f\n", (rightFF + rightFB));
        counter += 10;
        pros::delay(10);
    }

    leftFrontMotor = 0;
    leftBackMotor = 0;
    rightFrontMotor = 0;
    rightBackMotor = 0;
}

void ppMoveBackward(vector<vector<double>> initPoints, double spacing, double smoothVal1, double smoothVal2, double smoothTolerance, double maxVelocity, double maxAccel, double turnConstant, int lookAheadPointsNum, double trackWidth, double Kv, double Ka, double Kp, double Kc)
{
    //initPoints are all the points in the motion, including start and end
    //spacing is in inches between points
    //smoothVal1 should be 1-smoothVal2
    //smoothVal2 should be a value between 0.75 and 0.98
    //maxVelocity is the highest speed the robot is allowed to reach during this movement
    //maxAccel is the highest acceleration the robot is allowed to encounter during this movement
    //turnConstant should be between 1.0 and 5.0
    //lookAheadPointsNum is the number of points to look ahead
    //smoothTolerance default is 0.001
    /*trackWidth is measured from the robot. Due to turning scrub,
     *you want to use a track width a few inches larger than the real one.*/
    /*start Kv at 1/maxVelocity and start all other constants at 0
      *Tune Kv until the velocities match up
      *Set Ka to 0.002
      *Tune until accelerating and decelerating velocities are near accurate
      *Start Kp at 0.01 and increase number to make more accurate
      *Setting Kp too high will result in a jittery motion*/
    //Kc is curvature constant
    int counter = 0;
    //calcPosition();
    vector<vector<double>> pointsList = {{0.0}};
    pointsList = {};
    if (initPoints.size() == 0)
    {
        return;
    }
    else if (initPoints.size() == 1)
    {
        pointsList = generateLinearPath(position.getPosition()[0], position.getPosition()[1], initPoints[0][0], initPoints[0][1], spacing);
    }
    else
    {
        pointsList = generateLinearPath(initPoints[0][0], initPoints[0][1], initPoints[1][0], initPoints[1][1], spacing);
        if (initPoints.size() > 2)
        {
            for (int i = 1; i < initPoints.size() - 1; i++)
            {
                vector<vector<double>> pointsList2 = generateLinearPath(initPoints[i][0], initPoints[i][1], initPoints[i + 1][0], initPoints[i + 1][1], spacing);
                pointsList.insert(pointsList.end(), pointsList2.begin(), pointsList2.end());
            }
            pointsList = smooth(pointsList, smoothVal1, smoothVal2, smoothTolerance);
        }
    }

    //vector <double> distanceList = calculateDistance(pointsList);
    vector<double> curveList = calculateCurve(pointsList);
    vector<double> velList = calculateVelocity(pointsList, curveList, maxVelocity, maxAccel, turnConstant);
    for (int i = 0; i < pointsList.size(); i++)
    {
        printf(".velList #%d: %.3f\n", i, velList[i]);
    }
    //for (int i = 0; i < curveList.size(); i++) {
    //  printf("curveList #%d: %.3f\n", i, curveList[i]);
    //}
    int closestPoint = 1;
    vector<double> velocities = {0.0, 0.0};
    currentTime = time(0);
    while (true)
    {
        printf(".Time: %.d", counter);
        //calcPosition();
        double x = position.getPosition()[0];
        double y = position.getPosition()[1];
        printf(".Location: (%.3f, %.3f, %.3f)\n", x, y, position.getTheta() * 180 / M_PI);
        vector<double> lookAheadPoint = {0.0};
        lookAheadPoint = {};
        double smallestDistance = sqrt(pow((pointsList[closestPoint][0] - x), 2) + pow((pointsList[closestPoint][1] - y), 2));
        for (int i = closestPoint + 1; i < pointsList.size(); i++)
        {
            double newDistance = sqrt(pow((pointsList[i][0] - x), 2) + pow((pointsList[i][1] - y), 2));
            if (smallestDistance > newDistance)
            {
                smallestDistance = newDistance;
                closestPoint = i;
            }
        }
        if (closestPoint < pointsList.size() - 1 - lookAheadPointsNum)
        {
            lookAheadPoint = findLookAheadPoint(x, y, pointsList, closestPoint, lookAheadPointsNum, spacing);
        }
        else
        {
            lookAheadPoint = pointsList[pointsList.size() - 1];
        }
        printf(".lookAheadPoint: (%.3f, %.3f)\n", lookAheadPoint[0], lookAheadPoint[1]);
        //might need to be distance for tolerance
        if (lookAheadPoint[0] == pointsList[pointsList.size() - 1][0] && lookAheadPoint[1] == pointsList[pointsList.size() - 1][1] && (closestPoint == pointsList.size() - 1))
        {
            printf(".here");
            break;
        }
        //printf("closestPoint: (%.3f,%.3f)\n", pointsList[closestPoint][0], pointsList[closestPoint][1]);

        double curvature = findCurvature(lookAheadPoint, x, y, Kc);
        //printf("Curvature: %.3f\n", curvature);
        //printf("curvature: %.3f\n", curvature);

        //Left wheel speed, right wheel speed, target velocity, accel
        velocities = findVelocities(curvature, trackWidth, velList[closestPoint], maxAccel, velocities[2]);
        //printf("velocities: (%.3f, %.3f)\n m/s", velocities[0], velocities[1]);

        double leftFF = Kv * velocities[0] + Ka * (velocities[3]);
        double rightFF = Kv * velocities[1] + Ka * (velocities[3]);
        double leftFB = Kp * (velocities[0] - (-1.0 * convertToMeters(leftFrontMotor.get_actual_velocity() + -1.0 * leftBackMotor.get_actual_velocity()) / 2.0));
        double rightFB = Kp * (velocities[1] - (-1.0 * convertToMeters(rightFrontMotor.get_actual_velocity() + -1.0 * rightBackMotor.get_actual_velocity()) / 2.0));

        //printf("Left FF: %.3f\n", (leftFF ));
        //printf("Left FB: %.3f\n", (leftFB));
        //printf("Right FF: %.3f\n", (rightFF));
        //printf("Right FB: %.3f\n", (rightFB));

        //printf("Motor Voltage (L): %.3f\n", convertToRPM(leftFF + leftFB) * 127.0 / 200.0);
        //printf("Motor Voltage (R): %.3f\n\n", convertToRPM(rightFF + rightFB) * 127.0 / 200.0);

        printf("%.3f,%.3f,%.3f,%.3f,%.3f\n", velocities[0], velocities[1], convertToMeters(-1.0 * (leftFrontMotor.get_actual_velocity() + leftBackMotor.get_actual_velocity()) / 2), -1.0 * convertToMeters((rightFrontMotor.get_actual_velocity() + rightBackMotor.get_actual_velocity()) / 2), closestPoint * 1.0);

        leftFrontMotor = -1.0 * convertToRPM(leftFF + leftFB) * 127.0 / 200;
        leftBackMotor = -1.0 * convertToRPM(leftFF + leftFB) * 127.0 / 200;
        rightFrontMotor = -1.0 * convertToRPM(rightFF + rightFB) * 127.0 / 200;
        rightBackMotor = -1.0 * convertToRPM(rightFF + rightFB) * 127.0 / 200;

        //printf("Left speed: %.3f m/s\n", leftFrontMotor.get_actual_velocity() * 100 / (2 * M_PI * 4.0 * 2.54 * 60);
        //printf("Right speed: %.3f m/s\n", rightFrontMotor.get_actual_velocitty() * 100 / (2 * M_PI * 4.0 * 2.54 * 60));

        //printf("leftSpeed: %.4f\n", (leftFF + leftFB));
        //printf("rightSpeed: %.4f\n", (rightFF + rightFB));
        counter += 10;
        pros::delay(10);
    }

    leftFrontMotor = 0;
    leftBackMotor = 0;
    rightFrontMotor = 0;
    rightBackMotor = 0;
}

void ppMoveLeft(vector<vector<double>> initPoints, double spacing, double smoothVal1, double smoothVal2, double smoothTolerance, double maxVelocity, double maxAccel, double turnConstant, int lookAheadPointsNum, double trackWidth, double Kv, double Ka, double Kp, double Kc)
{
    //initPoints are all the points in the motion, including start and end
    //spacing is in inches between points
    //smoothVal1 should be 1-smoothVal2
    //smoothVal2 should be a value between 0.75 and 0.98
    //maxVelocity is the highest speed the robot is allowed to reach during this movement
    //maxAccel is the highest acceleration the robot is allowed to encounter during this movement
    //turnConstant should be between 1.0 and 5.0
    //lookAheadPointsNum is the number of points to look ahead
    //smoothTolerance default is 0.001
    /*trackWidth is measured from the robot. Due to turning scrub,
     *you want to use a track width a few inches larger than the real one.*/
    /*start Kv at 1/maxVelocity and start all other constants at 0
      *Tune Kv until the velocities match up
      *Set Ka to 0.002
      *Tune until accelerating and decelerating velocities are near accurate
      *Start Kp at 0.01 and increase number to make more accurate
      *Setting Kp too high will result in a jittery motion*/
    //Kc is curvature constant
    int counter = 0;
    //calcPosition();
    vector<vector<double>> pointsList = {{0.0}};
    pointsList = {};
    if (initPoints.size() == 0)
    {
        return;
    }
    else if (initPoints.size() == 1)
    {
        pointsList = generateLinearPath(position.getPosition()[0], position.getPosition()[1], initPoints[0][0], initPoints[0][1], spacing);
    }
    else
    {
        pointsList = generateLinearPath(initPoints[0][0], initPoints[0][1], initPoints[1][0], initPoints[1][1], spacing);
        if (initPoints.size() > 2)
        {
            for (int i = 1; i < initPoints.size() - 1; i++)
            {
                vector<vector<double>> pointsList2 = generateLinearPath(initPoints[i][0], initPoints[i][1], initPoints[i + 1][0], initPoints[i + 1][1], spacing);
                pointsList.insert(pointsList.end(), pointsList2.begin(), pointsList2.end());
            }
            pointsList = smooth(pointsList, smoothVal1, smoothVal2, smoothTolerance);
        }
    }

    //vector <double> distanceList = calculateDistance(pointsList);
    vector<double> curveList = calculateCurve(pointsList);
    vector<double> velList = calculateVelocity(pointsList, curveList, maxVelocity, maxAccel, turnConstant);
    for (int i = 0; i < pointsList.size(); i++)
    {
        printf(".velList #%d: %.3f\n", i, velList[i]);
    }
    //for (int i = 0; i < curveList.size(); i++) {
    //  printf("curveList #%d: %.3f\n", i, curveList[i]);
    //}
    int closestPoint = 1;
    vector<double> velocities = {0.0, 0.0};
    currentTime = time(0);
    while (true)
    {
        printf(".Time: %.d", counter);
        //calcPosition();
        double x = position.getPosition()[0];
        double y = position.getPosition()[1];
        printf(".Location: (%.3f, %.3f, %.3f)\n", x, y, position.getTheta() * 180 / M_PI);
        vector<double> lookAheadPoint = {0.0};
        lookAheadPoint = {};
        double smallestDistance = sqrt(pow((pointsList[closestPoint][0] - x), 2) + pow((pointsList[closestPoint][1] - y), 2));
        for (int i = closestPoint + 1; i < pointsList.size(); i++)
        {
            double newDistance = sqrt(pow((pointsList[i][0] - x), 2) + pow((pointsList[i][1] - y), 2));
            if (smallestDistance > newDistance)
            {
                smallestDistance = newDistance;
                closestPoint = i;
            }
        }
        if (closestPoint < pointsList.size() - 1 - lookAheadPointsNum)
        {
            lookAheadPoint = findLookAheadPoint(x, y, pointsList, closestPoint, lookAheadPointsNum, spacing);
        }
        else
        {
            lookAheadPoint = pointsList[pointsList.size() - 1];
        }
        printf(".lookAheadPoint: (%.3f, %.3f)\n", lookAheadPoint[0], lookAheadPoint[1]);
        //might need to be distance for tolerance
        if (lookAheadPoint[0] == pointsList[pointsList.size() - 1][0] && lookAheadPoint[1] == pointsList[pointsList.size() - 1][1] && (closestPoint == pointsList.size() - 1))
        {
            printf(".here");
            break;
        }
        //printf("closestPoint: (%.3f,%.3f)\n", pointsList[closestPoint][0], pointsList[closestPoint][1]);

        double curvature = findCurvatureLeft(lookAheadPoint, x, y, Kc);
        //printf("Curvature: %.3f\n", curvature);
        //printf("curvature: %.3f\n", curvature);

        //Left wheel speed, right wheel speed, target velocity, accel
        velocities = findVelocities(curvature, trackWidth, velList[closestPoint], maxAccel, velocities[2]);
        //printf("velocities: (%.3f, %.3f)\n m/s", velocities[0], velocities[1]);

        double leftFF = Kv * velocities[0] + Ka * (velocities[3]);
        double rightFF = Kv * velocities[1] + Ka * (velocities[3]);
        double leftFB = Kp * (velocities[0] - (convertToMeters(leftFrontMotor.get_actual_velocity() + leftBackMotor.get_actual_velocity()) / 2.0));
        double rightFB = Kp * (velocities[1] - (convertToMeters(rightFrontMotor.get_actual_velocity() + rightBackMotor.get_actual_velocity()) / 2.0));

        //printf("Left FF: %.3f\n", (leftFF ));
        //printf("Left FB: %.3f\n", (leftFB));
        //printf("Right FF: %.3f\n", (rightFF));
        //printf("Right FB: %.3f\n", (rightFB));

        //printf("Motor Voltage (L): %.3f\n", convertToRPM(leftFF + leftFB) * 127.0 / 200.0);
        //printf("Motor Voltage (R): %.3f\n\n", convertToRPM(rightFF + rightFB) * 127.0 / 200.0);

        printf("%.3f,%.3f,%.3f,%.3f,%.3f\n", velocities[0], velocities[1], convertToMeters((leftFrontMotor.get_actual_velocity() + leftBackMotor.get_actual_velocity()) / 2), convertToMeters((rightFrontMotor.get_actual_velocity() + rightBackMotor.get_actual_velocity()) / 2), closestPoint * 1.0);

        leftFrontMotor = -1 * convertToRPM(leftFF + leftFB) * 127.0 / 200;
        leftBackMotor = convertToRPM(leftFF + leftFB) * 127.0 / 200;
        rightFrontMotor = convertToRPM(rightFF + rightFB) * 127.0 / 200;
        rightBackMotor = -1 * convertToRPM(rightFF + rightFB) * 127.0 / 200;

        //printf("Left speed: %.3f m/s\n", leftFrontMotor.get_actual_velocity() * 100 / (2 * M_PI * 4.0 * 2.54 * 60);
        //printf("Right speed: %.3f m/s\n", rightFrontMotor.get_actual_velocitty() * 100 / (2 * M_PI * 4.0 * 2.54 * 60));

        //printf("leftSpeed: %.4f\n", (leftFF + leftFB));
        //printf("rightSpeed: %.4f\n", (rightFF + rightFB));
        counter += 10;
        pros::delay(10);
    }

    leftFrontMotor = 0;
    leftBackMotor = 0;
    rightFrontMotor = 0;
    rightBackMotor = 0;
}

void ppMoveRight(vector<vector<double>> initPoints, double spacing, double smoothVal1, double smoothVal2, double smoothTolerance, double maxVelocity, double maxAccel, double turnConstant, int lookAheadPointsNum, double trackWidth, double Kv, double Ka, double Kp, double Kc)
{
    //initPoints are all the points in the motion, including start and end
    //spacing is in inches between points
    //smoothVal1 should be 1-smoothVal2
    //smoothVal2 should be a value between 0.75 and 0.98
    //maxVelocity is the highest speed the robot is allowed to reach during this movement
    //maxAccel is the highest acceleration the robot is allowed to encounter during this movement
    //turnConstant should be between 1.0 and 5.0
    //lookAheadPointsNum is the number of points to look ahead
    //smoothTolerance default is 0.001
    /*trackWidth is measured from the robot. Due to turning scrub,
     *you want to use a track width a few inches larger than the real one.*/
    /*start Kv at 1/maxVelocity and start all other constants at 0
      *Tune Kv until the velocities match up
      *Set Ka to 0.002
      *Tune until accelerating and decelerating velocities are near accurate
      *Start Kp at 0.01 and increase number to make more accurate
      *Setting Kp too high will result in a jittery motion*/
    //Kc is curvature constant
    int counter = 0;
    //calcPosition();
    vector<vector<double>> pointsList = {{0.0}};
    pointsList = {};
    if (initPoints.size() == 0)
    {
        return;
    }
    else if (initPoints.size() == 1)
    {
        pointsList = generateLinearPath(position.getPosition()[0], position.getPosition()[1], initPoints[0][0], initPoints[0][1], spacing);
    }
    else
    {
        pointsList = generateLinearPath(initPoints[0][0], initPoints[0][1], initPoints[1][0], initPoints[1][1], spacing);
        if (initPoints.size() > 2)
        {
            for (int i = 1; i < initPoints.size() - 1; i++)
            {
                vector<vector<double>> pointsList2 = generateLinearPath(initPoints[i][0], initPoints[i][1], initPoints[i + 1][0], initPoints[i + 1][1], spacing);
                pointsList.insert(pointsList.end(), pointsList2.begin(), pointsList2.end());
            }
            pointsList = smooth(pointsList, smoothVal1, smoothVal2, smoothTolerance);
        }
    }

    //vector <double> distanceList = calculateDistance(pointsList);
    vector<double> curveList = calculateCurve(pointsList);
    vector<double> velList = calculateVelocity(pointsList, curveList, maxVelocity, maxAccel, turnConstant);
    for (int i = 0; i < pointsList.size(); i++)
    {
        printf(".velList #%d: %.3f\n", i, velList[i]);
    }
    //for (int i = 0; i < curveList.size(); i++) {
    //  printf("curveList #%d: %.3f\n", i, curveList[i]);
    //}
    int closestPoint = 1;
    vector<double> velocities = {0.0, 0.0};
    currentTime = time(0);
    while (true)
    {
        printf(".Time: %.d", counter);
        //calcPosition();
        double x = position.getPosition()[0];
        double y = position.getPosition()[1];
        printf(".Location: (%.3f, %.3f, %.3f)\n", x, y, position.getTheta() * 180 / M_PI);
        vector<double> lookAheadPoint = {0.0};
        lookAheadPoint = {};
        double smallestDistance = sqrt(pow((pointsList[closestPoint][0] - x), 2) + pow((pointsList[closestPoint][1] - y), 2));
        for (int i = closestPoint + 1; i < pointsList.size(); i++)
        {
            double newDistance = sqrt(pow((pointsList[i][0] - x), 2) + pow((pointsList[i][1] - y), 2));
            if (smallestDistance > newDistance)
            {
                smallestDistance = newDistance;
                closestPoint = i;
            }
        }
        if (closestPoint < pointsList.size() - 1 - lookAheadPointsNum)
        {
            lookAheadPoint = findLookAheadPoint(x, y, pointsList, closestPoint, lookAheadPointsNum, spacing);
        }
        else
        {
            lookAheadPoint = pointsList[pointsList.size() - 1];
        }
        printf(".lookAheadPoint: (%.3f, %.3f)\n", lookAheadPoint[0], lookAheadPoint[1]);
        //might need to be distance for tolerance
        if (lookAheadPoint[0] == pointsList[pointsList.size() - 1][0] && lookAheadPoint[1] == pointsList[pointsList.size() - 1][1] && (closestPoint == pointsList.size() - 1))
        {
            printf(".here");
            break;
        }
        //printf("closestPoint: (%.3f,%.3f)\n", pointsList[closestPoint][0], pointsList[closestPoint][1]);

        double curvature = findCurvatureRight(lookAheadPoint, x, y, Kc);
        //printf("Curvature: %.3f\n", curvature);
        //printf("curvature: %.3f\n", curvature);

        //Left wheel speed, right wheel speed, target velocity, accel
        velocities = findVelocities(curvature, trackWidth, velList[closestPoint], maxAccel, velocities[2]);
        //printf("velocities: (%.3f, %.3f)\n m/s", velocities[0], velocities[1]);

        double leftFF = Kv * velocities[0] + Ka * (velocities[3]);
        double rightFF = Kv * velocities[1] + Ka * (velocities[3]);
        double leftFB = Kp * (velocities[0] - (convertToMeters(leftFrontMotor.get_actual_velocity() + leftBackMotor.get_actual_velocity()) / 2.0));
        double rightFB = Kp * (velocities[1] - (convertToMeters(rightFrontMotor.get_actual_velocity() + rightBackMotor.get_actual_velocity()) / 2.0));

        //printf("Left FF: %.3f\n", (leftFF ));
        //printf("Left FB: %.3f\n", (leftFB));
        //printf("Right FF: %.3f\n", (rightFF));
        //printf("Right FB: %.3f\n", (rightFB));

        //printf("Motor Voltage (L): %.3f\n", convertToRPM(leftFF + leftFB) * 127.0 / 200.0);
        //printf("Motor Voltage (R): %.3f\n\n", convertToRPM(rightFF + rightFB) * 127.0 / 200.0);

        printf("%.3f,%.3f,%.3f,%.3f,%.3f\n", velocities[0], velocities[1], convertToMeters((leftFrontMotor.get_actual_velocity() + leftBackMotor.get_actual_velocity()) / 2), convertToMeters((rightFrontMotor.get_actual_velocity() + rightBackMotor.get_actual_velocity()) / 2), closestPoint * 1.0);

        leftFrontMotor = convertToRPM(leftFF + leftFB) * 127.0 / 200;
        leftBackMotor = -1 * convertToRPM(leftFF + leftFB) * 127.0 / 200;
        rightFrontMotor = -1 * convertToRPM(rightFF + rightFB) * 127.0 / 200;
        rightBackMotor = convertToRPM(rightFF + rightFB) * 127.0 / 200;

        //printf("Left speed: %.3f m/s\n", leftFrontMotor.get_actual_velocity() * 100 / (2 * M_PI * 4.0 * 2.54 * 60);
        //printf("Right speed: %.3f m/s\n", rightFrontMotor.get_actual_velocitty() * 100 / (2 * M_PI * 4.0 * 2.54 * 60));

        //printf("leftSpeed: %.4f\n", (leftFF + leftFB));
        //printf("rightSpeed: %.4f\n", (rightFF + rightFB));
        counter += 10;
        pros::delay(10);
    }

    leftFrontMotor = 0;
    leftBackMotor = 0;
    rightFrontMotor = 0;
    rightBackMotor = 0;
}