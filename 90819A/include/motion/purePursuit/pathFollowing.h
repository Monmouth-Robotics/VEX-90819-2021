#ifndef _PATH_FOLLOWING
#define _PATH_FOLLOWING
#include "api.h"
#include "init/utility.h"
#include "motion/purePursuit/pathGeneration.h"
#include "init/taskManagement.h"
#include <vector>

using namespace std;

vector<double> getErrors(vector<double> currentPosition, vector<double>lookAheadPosition);
void moveRobot(vector<double> errors, double distanceError, double kPDistance, double kPAngle);
void ppMove(vector<vector<double>> initPoints, double spacing, double smoothVal1, double smoothVal2, double smoothTolerance, double maxVel, double maxAccel, double turnConstant, int lookAheadPointsNum, double thresholdError, double kPDistance, double kPAngle, double angleThreshold);
vector<double> findLookAheadPoint(double x, double y, vector<vector<double>> pointsList, int closestPoint, int lookAheadPointsNum, double lookAheadDistance);

#endif
