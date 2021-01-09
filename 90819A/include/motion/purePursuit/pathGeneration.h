#ifndef _PATH_GENERATION
#define _PATH_GENERATION

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "init/utility.h"
#include "init/taskManagement.h"
#include <vector>

using namespace std;

class PathGeneration {
public:
	PathGeneration();
	PathGeneration& withPath(vector<vector<double>> initPoints, double spacing);
	PathGeneration& withSmoothing(double smoothVal1, double smoothVal2, double smoothTolerance);
	PathGeneration& withLimits(double maxVel, double maxAccel);
	PathGeneration& withTurnConstant(double turnConstant);
	vector<vector<double>> generatePath();
private:
	vector<vector<double>> generateLinearPath(double initX, double initY, double initTheta, double finalX, double finalY, double finalTheta, double spacing);
	vector<vector<double>> smooth(vector<vector<double>> pointsList, double a, double b, double tolerance);
	vector<double> calculateCurve(vector<vector<double>> pointsList);
	vector<double> calculateVelocity(vector<vector<double>> pointsList, vector<double> curveList, double maxVelocity, double maxAccel, double turnConstant);
	static vector<vector<double>> initPoints;
	static double spacing;
	static double smoothVal1;
	static double smoothVal2;
	static double smoothTolerance;
	static double maxVel;
	static double maxAccel;
	static double turnConstant;
};

#endif
