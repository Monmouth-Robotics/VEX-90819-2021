#ifndef _PATH_GENERATION
#define _PATH_GENERATION
#include "api.h"
#include "positioning/positionAlg.h"
#include "macros/indexing.h"
#include "init/utility.h"
#include <vector>

using namespace std;

extern PositionAlg position;

vector<vector<double>> generateLinearPath(double initX, double initY, double finalX, double finalY, double spacing);
vector<vector<double>> smooth(vector<vector<double>> pointsList, double a, double b, double tolerance);
vector<vector<double>> generatePath(vector<vector<double>> initPoints, double spacing, double smoothVal1, double smoothVal2, double smoothTolerance, double maxVel, double maxAccel);

#endif
