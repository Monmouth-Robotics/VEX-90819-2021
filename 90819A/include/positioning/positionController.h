#ifndef _POSITION_CONTROLLER
#define _POSITION_CONTROLLER

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
#include "init/devices.h"
#include "init/utility.h"

#include <vector>

using namespace std;

class PositionController
{
public:
	PositionController();
	static void calcPosition(void *ignore);
	vector<double> getPosition();
	void resetGlobal();
	double getTheta();
	double getSpeed();
	void setTheta(double newTheta);
	void setPosition(double x, double y);

private:
	static double WHEEL_DIAMETER;
	static double DISTANCE_TO_LEFT_ENCODER;
	static double DISTANCE_TO_RIGHT_ENCODER;
	static double DISTANCE_TO_BACK_ENCODER;

	static double previousLeftEncoderDegrees;
	static double previousRightEncoderDegrees;
	static double previousBackEncoderDegrees;

	static double leftEncoderDegrees;
	static double rightEncoderDegrees;
	static double backEncoderDegrees;

	static double leftEncoderDegreesDifference;
	static double rightEncoderDegreesDifference;
	static double backEncoderDegreesDifference;

	static double leftEncoderRadians;
	static double rightEncoderRadians;
	static double backEncoderRadians;

	static double leftEncoderDistance;
	static double rightEncoderDistance;
	static double backEncoderDistance;

	static double deltaTheta;
	static double polarTheta;
	static double theta;

	static double robotSpeed;

	static vector<double> positionVector;
	static vector<double> newVector;

	static vector<double> testVector;
	static vector<double> leftVector;
	static vector<double> rightVector;

	static double x;
	static double y;
	static double r;
	static double newX;
	static double newY;
	static double thetaM;

	static double inertLeft;
	static double inertLeftOffset;
	static double inertRight;
	static double inertRightOffset;
	static double inertCenter;
	static double inertCenterOffset;
};

#endif
