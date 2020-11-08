#include "positioning/positionAlg.h"

bool ready = false;

int currentL = 0;
int currentR = 0;
int deltaL = 0;
int deltaR = 0;
int lastDeltaL = 0;
int lastDeltaR = 0;

double inertL = 0;
double inertR = 0;
double inertT = 0;

double thetaRad = 0;
double thetaDeg = 0;
double offset = 0;
double posX = 0;
double posY = 0;

double output = 0;
double Desiredtheta = 0;
double DesiredX = 0;
double DesiredY = 0;

double Inertial::getTheta()
{
	return thetaRad;
}

void Inertial::initialize(void* ignore)
{
	imuLeft.reset();
	imuRight.reset();

	int time = pros::millis();
	int iter = 0;

	while (imuLeft.is_calibrating() || imuRight.is_calibrating()) {
		printf("IMU calibrating... %d\n", iter);
		iter += 10;
		pros::delay(10);
		
	}
	printf("IMU is done calibrating (took %d ms)\n", iter - time);
	ready = true;
}

void Inertial::calcAngle(void* ignore)
{

	// double offset = 0;
	while (true)
	{
		if (ready) {
			inertL = abs(imuLeft.get_heading() - 360) * M_PI / 180;
			inertR = abs(imuLeft.get_heading() - 360) * M_PI / 180;

			float x = (cos(inertL - offset + M_PI) + cos(inertR - offset + M_PI)) / 2;
			float y = (sin(inertL - offset + M_PI) + sin(inertR - offset + M_PI)) / 2;

			thetaRad = abs(atan2f(y, x) + M_PI);
			thetaDeg = thetaRad * 180 / M_PI;

			currentL = leftEncoder.get_value();
			currentR = rightEncoder.get_value();

			deltaL = currentL - lastDeltaL;
			deltaR = currentR - lastDeltaR;

			posX = posX + ((deltaL + deltaR) / 2) * cos(thetaRad);
			posY = posY + ((deltaL + deltaR) / 2) * sin(thetaRad);

			lastDeltaL = leftEncoder.get_value();
			lastDeltaR = rightEncoder.get_value();

			pros::delay(20);
		}
	}

}

void Inertial::reset() {
	float left = abs(imuLeft.get_heading() - 360) * M_PI / 180;
	float right = abs(imuRight.get_heading() - 360) * M_PI / 180;

	float x = (cos(left + M_PI) + cos(right + M_PI)) / 2;
	float y = (sin(left + M_PI) + sin(right + M_PI)) / 2;

	offset = abs(atan2f(y, x) + M_PI);
}
