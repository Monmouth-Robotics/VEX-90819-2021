#ifndef _PURE_PURSUIT
#define _PURE_PURSUIT
#include "api.h"
#include "positioning/positionAlg.h"
#include "macros/indexing.h"
#include <vector>

using namespace std;

extern PositionAlg position;
extern Indexing indexer;
extern pros::Task indexController;

void ppMoveForward(vector<vector<double>> initPoints, double spacing, double smoothVal1, double smoothVal2, double smoothTolerance, double maxVelocity, double maxAccel, double turnConstant, int lookAheadPointsNum, double trackWidth, double Kv, double Ka, double Kp, double Kc);
void ppMoveBackward(vector<vector<double>> initPoints, double spacing, double smoothVal1, double smoothVal2, double smoothTolerance, double maxVelocity, double maxAccel, double turnConstant, int lookAheadPointsNum, double trackWidth, double Kv, double Ka, double Kp, double Kc);
void ppMoveLeft(vector<vector<double>> initPoints, double spacing, double smoothVal1, double smoothVal2, double smoothTolerance, double maxVelocity, double maxAccel, double turnConstant, int lookAheadPointsNum, double trackWidth, double Kv, double Ka, double Kp, double Kc);
void ppMoveRight(vector<vector<double>> initPoints, double spacing, double smoothVal1, double smoothVal2, double smoothTolerance, double maxVelocity, double maxAccel, double turnConstant, int lookAheadPointsNum, double trackWidth, double Kv, double Ka, double Kp, double Kc);

#endif
