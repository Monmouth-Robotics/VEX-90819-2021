#ifndef _PATH_GENERATION
#define _PATH_GENERATION
#include "api.h"
#include "init/utility.h"
#include "init/taskManagement.h"
#include <vector>

using namespace std;

extern PositionAlg position;

vector<vector<double>> generateLinearPath(double initX, double initY, double initTheta, double finalX, double finalY, double finalTheta, double spacing);
vector<vector<double>> smooth(vector<vector<double>> pointsList, double a, double b, double tolerance);
vector<vector<double>> generatePath(vector<vector<double>> initPoints, double spacing, double smoothVal1, double smoothVal2, double smoothTolerance, double maxVel, double maxAccel, double turnConstant);

#endif
