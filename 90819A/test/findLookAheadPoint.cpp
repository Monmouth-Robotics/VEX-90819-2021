#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdio>
#include <vector>


using namespace std;

/**
 * Calculates signed difference between two headings
 */
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

/**
 * Calculates dot product of two vectors
 */
double dot(vector<double> a, vector<double> b)
{
	return a[0] * b[0] + a[1] * b[1];
}

vector<double> findLookAheadPoint(double x, double y, vector<vector<double>> pointsList, int closestPoint, int lookAheadPointsNum, double spacing)
{
	//Starting point of the line segment
	vector<double> E = { 0.0, 0.0 };
	E = { pointsList[closestPoint][0], pointsList[closestPoint][1] };

	//End point of the line segment
	vector<double> L = { 0.0, 0.0 };
	L = { pointsList[closestPoint + lookAheadPointsNum][0], pointsList[closestPoint + lookAheadPointsNum][1] };

	//Center of the drawn circle, representing the robot position
	vector<double> C = { 0.0, 0.0 };
	C = { x, y };

	//Direction vector from starting point to ending point
	vector<double> d = { 0.0, 0.0 };
	d = { L[0] - E[0], L[1] - E[1] };

	//Vector drawn from center of robot to starting point
	vector<double> f = { 0.0, 0.0 };
	f = { E[0] - C[0], E[1] - C[1] };

	//Represents the lookahead distance
	double r = spacing * lookAheadPointsNum;

	//Determines number of intersections between circle around robot and path
	double a = dot(d, d);
	double b = 2 * dot(f, d);
	double c = dot(f, f) - r * r;
	double discriminant = b * b - 4 * a * c;

	if (closestPoint + lookAheadPointsNum < pointsList.size())
	{
		return pointsList[closestPoint + lookAheadPointsNum];
	}
	else {
		return pointsList[pointsList.size() - 1];
	}

	//Represents no intersection
	if (discriminant < 0)
	{
		//If the current lookahead point is not the last point, it can expand its search radius
		if (closestPoint != pointsList.size() - lookAheadPointsNum - 1)
		{
			//Recursive function with a greater number of lookahead points
			return findLookAheadPoint(x, y, pointsList, closestPoint, lookAheadPointsNum + 1, spacing);
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
			return { E[0] + t1 * d[0], E[1] + t1 * d[1] };
		}
		else if (t2 >= 0 && t2 <= 1)
		{
			return { E[0] + t2 * d[0], E[1] + t2 * d[1] };
		}
		//Expands search radius if both points found are behind the current point in the motion
		else
		{
			if (closestPoint != pointsList.size() - lookAheadPointsNum - 1)
			{
				//Recursive function with a greater number of lookahead points
				return findLookAheadPoint(x, y, pointsList, closestPoint, lookAheadPointsNum + 1, spacing);
			}
			else
			{
				//Returns the last point in the list
				return pointsList[pointsList.size() - 1];
			}
		}
	}
}

vector<vector<double>> generateLinearPath(double initX, double initY, double initTheta, double finalX, double finalY, double finalTheta, double spacing)
{
	vector<vector<double>> pointsList = { {0.0} };
	pointsList = {};

	//Finds the vector drawn from the start point to the end point
	vector<double> changeVector = { finalX - initX, finalY - initY };

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
		vector<double> newVector = { initX + changeVector[0] * i, initY + changeVector[1] * i, 10 };
		pointsList.push_back(newVector);
	}

	//Add the ending point to the list
	vector<double> finalVector{ finalX, finalY, finalTheta };
	pointsList.push_back(finalVector);

	double totalChange = calcAngleDiff(finalTheta, initTheta);
	double maxChange = totalChange / (pointsList.size() - 1);

	for (int i = 0; i < pointsList.size(); i++)
	{
		pointsList[i][2] = initTheta + i * maxChange;
	}

	return pointsList;
}

vector<vector<double>> generatePath(vector<vector<double>> initPoints, double spacing)
{
	//Initialize points list as an empty vector
	vector<vector<double>> pointsList = { {0.0} };
	pointsList = {};

	vector<vector<double>> pointsList2 = { {0.0} };
	pointsList2 = {};

	//Invalid call if no points are defined
	if (initPoints.size() == 0)
	{
		return pointsList;
	}

	//Generates path between each pair of consecutive points
	else
	{
		pointsList = generateLinearPath(initPoints[0][0], initPoints[0][1], initPoints[0][2], initPoints[1][0], initPoints[1][1], initPoints[1][2], spacing);

		if (initPoints.size() > 2)
		{
			for (int i = 1; i < initPoints.size() - 1; i++)
			{

				pointsList2 = generateLinearPath(initPoints[i][0], initPoints[i][1], initPoints[i][2], initPoints[i + 1][0], initPoints[i + 1][1], initPoints[i + 1][2], spacing);

				pointsList.pop_back();
				//Inserts each subsequent list at the end of the original
				for (int i = 0; i < pointsList2.size(); i++) {
					pointsList.push_back({ pointsList2[i][0], pointsList2[i][1], pointsList2[i][2] });
				}
			}
		}
	}

	return pointsList;
}

int main() {
	vector<vector<double>> pointsList = { {0.000, 0.000, 6.283}, {0.000, 1.000, 6.283}, {0.000, 2.000, 6.283}, {0.000, 3.000, 6.283}, {0.000, 4.000, 6.283}, {0.000, 5.000, 6.283}, {0.000, 6.000, 6.283}, {0.000, 7.000, 6.283}, {0.000, 8.000, 6.283}, {0.000, 9.000, 6.283}, {0.000, 10.000, 6.283}, {0.000, 11.000, 6.283}, {0.000, 12.000, 6.283}, {0.000, 13.000, 6.283}, {0.000, 14.000, 6.283}, {0.000, 15.000, 6.283}, {0.000, 16.000, 6.283}, {0.000, 17.000, 6.283}, {0.000, 18.000, 6.283}, {0.000, 19.000, 6.283}, {0.000, 20.000, 6.283}, {0.707, 20.707, 6.310}, {1.414, 21.414, 6.337}, {2.121, 22.121, 6.364}, {2.828, 22.828, 6.392}, {3.536, 23.536, 6.419}, {4.243, 24.243, 6.446}, {4.950, 24.950, 6.473}, {5.657, 25.657, 6.500}, {6.364, 26.364, 6.527}, {7.071, 27.071, 6.554}, {7.778, 27.778, 6.581}, {8.485, 28.485, 6.608}, {9.192, 29.192, 6.635}, {9.899, 29.899, 6.662}, {10.607, 30.607, 6.689}, {11.314, 31.314, 6.717}, {12.021, 32.021, 6.744}, {12.728, 32.728, 6.771}, {13.435, 33.435, 6.798}, {14.142, 34.142, 6.825}, {14.849, 34.849, 6.852}, {15.556, 35.556, 6.879}, {16.263, 36.263, 6.906}, {16.971, 36.971, 6.933}, {17.678, 37.678, 6.960}, {18.385, 38.385, 6.987}, {19.092, 39.092, 7.014}, {19.799, 39.799, 7.042}, {20.000, 40.000, 7.069} };

	vector<double> lookAheadPoint = findLookAheadPoint(1.088, 18.447, pointsList, 19, 6, 1);

	printf("Lookahead Point: (%.3f, %.3f, %.3f)", lookAheadPoint[0], lookAheadPoint[1], lookAheadPoint[2]);

	return 0;
}