#include "motion/purePursuit/pathGeneration.h"

vector<vector<double>> generateLinearPath(double initX, double initY, double initTheta, double finalX, double finalY, double finalTheta, double spacing)
{
    vector<vector<double>> pointsList = {{0.0}};
    pointsList = {};

    //Finds the vector drawn from the start point to the end point
    vector<double> changeVector = {finalX - initX, finalY - initY};

    //Uses Pythagorean theorem to calculate magnitude of changeVector
    double magnitude = sqrt(pow(changeVector[0], 2) + pow(changeVector[1], 2));

    //Calculates the number of waypoints that need to be drawn
    double numPoints = ceil(magnitude / spacing);

    //Find the unit vector and multiply by spacing
    changeVector[0] = changeVector[0] * spacing / magnitude;
    changeVector[1] = changeVector[1] * spacing / magnitude;

    //Traverse through each point and save each point into vector
    for (int i = 0; i < numPoints; i++)
    {
        vector<double> newVector = {initX + changeVector[0] * i, initY + changeVector[1] * i, 10};
        pointsList.push_back(newVector);
    }

    //Add the ending point to the list
    vector<double> finalVector{finalX, finalY};
    pointsList.push_back(finalVector);

    // for (int i = 0; i<pointsList.size(); i++){
    //     pointsList[i][2] = 10;
    // }

    double totalChange = calcAngleDiff(finalTheta, initTheta);
    double maxChange = totalChange / (pointsList.size() - 1);

    for (int i = 0; i < pointsList.size(); i++)
    {
        pointsList[i][2] = initTheta + i * maxChange;
    }

    // for (int i = 0; i < pointsList.size(); i++)
    // {
    //     printf("(%.3f, %.3f, %.3f)\n", pointsList[i][0], pointsList[i][1], pointsList[i][2]);
    // }

    return pointsList;
}

vector<vector<double>> smooth(vector<vector<double>> pointsList, double a, double b, double tolerance)
{
    //Copy vector
    vector<vector<double>> newPointsList = pointsList;

    double change = tolerance;

    //Loops until change is within the acceptable tolerance
    while (change >= tolerance)
    {
        change = 0.0;

        //Loops through all points
        for (int i = 1; i < pointsList.size() - 1; i++)
        {
            //Loops through x and y coordinates for each point
            for (int j = 0; j < 2; j++)
            {
                //Creates an auxiliary variable for manipulation
                double aux = newPointsList[i][j];

                //Creates new point based on weight data and weight of smoothing
                newPointsList[i][j] += a * (pointsList[i][j] - newPointsList[i][j]) + b * (newPointsList[i - 1][j] + newPointsList[i + 1][j] - (2.0 * newPointsList[i][j]));

                //Updates change based on new point
                change += abs(aux - newPointsList[i][j]);
            }
        }
    }
    return newPointsList;
}

vector<double> calculateCurve(vector<vector<double>> pointsList)
{
    //Initialize curve list as vector with the first value as 0.0
    vector<double> curveList = {0.0};
    curveList = {};
    curveList.push_back(0.0);

    //Calculate curvature at each point excluding the first and last points
    for (int i = 1; i < pointsList.size() - 1; i++)
    {
        //Gets the x-coordinates of the current point and previous point
        double x1 = pointsList[i][0];
        double x2 = pointsList[i - 1][0];

        //Prevents error when dividing by (x1-x2)
        if (x1 == x2)
        {
            x1 += 0.001;
        }

        //Gets the x-coordinate of the next point
        double x3 = pointsList[i + 1][0];

        //Gets the y-coordinate of the current, previous, and next points
        double y1 = pointsList[i][1];
        double y2 = pointsList[i - 1][1];
        double y3 = pointsList[i + 1][1];

        //Intermediate constants used for calculations
        double k1 = 0.5 * (pow(x1, 2) + pow(y1, 2) - pow(x2, 2) - pow(y2, 2)) / (x1 - x2);
        double k2 = (y1 - y2) / (x1 - x2);
        double b = 0.5 * (pow(x2, 2) - 2 * x2 * k1 + pow(y2, 2) - pow(x3, 2) + 2 * x3 * k1 - pow(y3, 2)) / (x3 * k2 - y3 + y2 - x2 * k2);
        double a = k1 - k2 * b;

        //Push curvature value to vector
        curveList.push_back(1 / sqrt(pow(x1 - a, 2) + pow(y1 - b, 2)));
    }

    //Add curvature at last point as 0.0
    curveList.push_back(0.0);
    return curveList;
}

vector<double> calculateVelocity(vector<vector<double>> pointsList, vector<double> curveList, double maxVelocity, double maxAccel, double turnConstant)
{
    //Initialize max velocity list as empty vector
    vector<double> maxVelList = {0.0};
    maxVelList = {};

    //Calculate max velocity at each individual point
    for (int i = 0; i < curveList.size(); i++)
    {
        //Prevents divide by 0 error
        if (curveList[i] == 0.0)
        {
            curveList[i] = 0.001;
        }

        //Adds max velocity based on curvature, turnConstant, and maxVelocity, defined by parameters
        maxVelList.push_back(min(maxVelocity, (turnConstant / curveList[i])));
    }

    //Initialize target velocity list as vector with first value as 0.0
    vector<double> targetVelList = {0};
    targetVelList = {};
    targetVelList.push_back(0.0);

    //Set initial value to 0.0
    double prevVel = 0.0;

    //Calculate target velocity at each individual point
    for (int i = 1; i < maxVelList.size(); i++)
    {
        //Calculates new velocity based on previous velocity and limits set by parameters
        prevVel = sqrt(pow(prevVel, 2) + 2 * maxAccel * 0.0254 * sqrt(pow((pointsList[i][0] - pointsList[i - 1][0]), 2) + pow((pointsList[i][1] - pointsList[i - 1][1]), 2)));

        //Verifies that the value does not exceed max limit
        if (prevVel > maxVelList[i])
        {
            prevVel = maxVelList[i];
        }

        targetVelList.push_back(prevVel);
    }

    //Initialize actual velocity list as vector with all values set to 0.0 and the same size as max velocity list
    vector<double> velList(maxVelList.size(), 0.0);

    //Set initial value to 0.0
    double previousVel = 0.0;

    //Calculate actual velocity at each individual point
    for (int i = maxVelList.size() - 2; i >= 0; i--)
    {

        //Calculates distance between two consecutive points
        double distance = sqrt(pow((pointsList[i + 1][0] - pointsList[i][0]), 2) + pow((pointsList[i + 1][1] - pointsList[i][1]), 2));

        //Convert distance from inches to meters
        distance = distance * 0.0254;

        //Calculates new velocity based on max limit set by parameters
        previousVel = min(targetVelList[i], sqrt(pow(previousVel, 2) + 2 * maxAccel * distance));

        velList[i] = previousVel;
    }

    return velList;
}

vector<vector<double>> generatePath(vector<vector<double>> initPoints, double spacing, double smoothVal1, double smoothVal2, double smoothTolerance, double maxVel, double maxAccel, double turnConstant)
{
    //Initialize points list as an empty vector
    printf("here\n");
    vector<vector<double>> pointsList = {{0.0}};
    pointsList = {};

    vector<vector<double>> pointsList2 = {{0.0}};
    pointsList2 = {};

    //Invalid call if no points are defined
    if (initPoints.size() == 0)
    {
        return pointsList;
    }

    //Generates path from current robot position to provided coordinate
    // else if (initPoints.size() == 1)
    // {
    // 	pointsList = generateLinearPath(position.getPosition()[0], position.getPosition()[1], initPoints[0][0], initPoints[0][1], spacing);
    // }

    //Generates path between each pair of consecutive points
    else
    {
        pointsList = generateLinearPath(initPoints[0][0], initPoints[0][1], initPoints[0][2], initPoints[1][0], initPoints[1][1], initPoints[1][2], spacing);

        if (initPoints.size() > 2)
        {
            for (int i = 1; i < initPoints.size() - 1; i++)
            {
                // printf("%.3f, %.3f, %.3f\n", initPoints[i][0], initPoints[i][1], initPoints[i][2]);
                // printf("%.3f, %.3f, %.3f\n", initPoints[i + 1][0], initPoints[i + 1][1], initPoints[i + 1][2]);

                pointsList2 = generateLinearPath(initPoints[i][0], initPoints[i][1], initPoints[i][2], initPoints[i + 1][0], initPoints[i + 1][1], initPoints[i + 1][2], spacing);

                pointsList.pop_back();
                //Inserts each subsequent list at the end of the original
                for (int i = 0; i<pointsList2.size(); i++){
                    pointsList.push_back ({pointsList2[i][0], pointsList2[i][1], pointsList2[i][2]});
                }
            }
            
            
            //Smooths entire points list
            pointsList = smooth(pointsList, smoothVal1, smoothVal2, smoothTolerance);
        }
    }
    //Calculate curvature along every point on the path
    vector<double> curveList = calculateCurve(pointsList);

    //Calculate velocity along every point on the path
    vector<double> velList = calculateVelocity(pointsList, curveList, maxVel, maxAccel, turnConstant);

    // //Velocity is third value stored for each point
    // for (int i = 0; i < velList.size(); i++) {
    // 	pointsList[i][2] = velList[i];
    // }

    for (int i = 0; i < pointsList.size(); i++)
    {
        printf("(%.3f, %.3f, %.3f)\n", pointsList[i][0], pointsList[i][1], pointsList[i][2]);
    }

    return pointsList;
}