#ifndef _PATH_FOLLOWING
#define _PATH_FOLLOWING

#include "api.h"
#include "init/utility.h"
#include "motion/purePursuit/pathGeneration.h"
#include "init/taskManagement.h"
#include <vector>

using namespace std;

namespace zoo {
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
		static vector<vector<double>> initPoints;
		static double spacing;
		static double smoothVal1;
		static double smoothVal2;
		static double smoothTolerance;
		static double maxVel;
		static double maxAccel;
		static double turnConstant;
		static int lookAheadPointsNum;
		static double thresholdError;
		static double kPDistance;
		static double kPAngle;
		static double angleThreshold;
		static double speedCheckDistance;
		static double speedCheckSpeed;
		static double speedCheckTime;
		static double minPower;
		static double resetX;
		static double resetY;
		static double resetTheta;
		static vector<double> getErrors(vector<double> currentPosition, vector<double> lookAheadPosition);
		static double findPercentage(double xError, double yError);
		static void moveRobot(vector<double> errors, double distanceError, double kPDistance, double kPAngle, double minPower);
		static vector<double> findLookAheadPoint(double x, double y, vector<vector<double>> pointsList, int closestPoint, int lookAheadPointsNum, double lookAheadDistance);
	};
}

#endif
