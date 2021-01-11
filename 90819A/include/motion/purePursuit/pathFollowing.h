#ifndef _PATH_FOLLOWING
#define _PATH_FOLLOWING

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "init/utility.h"
#include "motion/purePursuit/pathGeneration.h"
#include "positioning/positionController.h"
#include <vector>

using namespace std;

class PathFollowing {
public:
	explicit PathFollowing();
	void ppMove();
	PathFollowing& withPath(vector<vector<double>> initPoints, double spacing);
	PathFollowing& withSmoothing(double smoothVal1, double smoothVal2, double smoothTolerance);
	PathFollowing& withLimits(double maxVel, double maxAccel);
	PathFollowing& withLookAheadPointsNum(double lookAheadPointsNum);
	PathFollowing& withThresholdErrors(double thresholdError, double angleThreshold);
	PathFollowing& withGains(double kPDistance, double kPAngle);
	PathFollowing& withTurnConstant(double turnConstant);
	PathFollowing& withMinPower(double minPower);
	PathFollowing& withSpeedCheck(double speedCheckDistance, double speedCheckSpeed, double SpeedCheckTime);
	PathFollowing& withCoordinateReset(double resetX, double resetY);
	PathFollowing& withAngleReset(double resetTheta);
private:
	vector<vector<double>> initPoints;
	double spacing;
	double smoothVal1;
	double smoothVal2;
	double smoothTolerance;
	double maxVel;
	double maxAccel;
	double turnConstant;
	int lookAheadPointsNum;
	double thresholdError;
	double kPDistance;
	double kPAngle;
	double angleThreshold;
	double speedCheckDistance;
	double speedCheckSpeed;
	double speedCheckTime;
	double minPower;
	double resetX;
	double resetY;
	double resetTheta;
	bool coordinateReset;
	bool angleReset;
	static vector<double> getErrors(vector<double> currentPosition, vector<double> lookAheadPosition);
	static double findPercentage(double xError, double yError);
	static void moveRobot(vector<double> errors, double distanceError, double kPDistance, double kPAngle, double minPower);
	static vector<double> findLookAheadPoint(double x, double y, vector<vector<double>> pointsList, int closestPoint, int lookAheadPointsNum, double lookAheadDistance);
};

#endif
