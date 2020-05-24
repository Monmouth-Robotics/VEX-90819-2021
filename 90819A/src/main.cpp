#include "main.h"
#include <cmath>
#include <iostream> 
#include <list> 
#include <iterator> 
using namespace std;

#define _USE_MATH_DEFINES

pros::Controller controller(CONTROLLER_MASTER);

pros::Motor leftFrontMotor(18, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor leftBackMotor(20, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor rightFrontMotor(12, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
pros::Motor rightBackMotor(19, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);

pros::ADIEncoder leftEncoder('A', 'B', false);
pros::ADIEncoder rightEncoder('C', 'D', false);
pros::ADIEncoder backEncoder('E', 'F', false);


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
double WHEEL_DIAMETER = 4; //inches
double DISTANCE_TO_LEFT_ENCODER = 7.25; //inches
double DISTANCE_TO_RIGHT_ENCODER = 7.25; //inches
double DISTANCE_TO_BACK_ENCODER = 5.5; //inches

double previousLeftEncoderDegrees = 0;
double previousRightEncoderDegrees = 0;
double previousBackEncoderDegrees = 0;

double leftEncoderDegrees = 0;
double rightEncoderDegrees = 0;
double backEncoderDegrees = 0;

double leftEncoderDegreesDifference = 0;
double rightEncoderDegreesDifference = 0;
double backEncoderDegreesDifference = 0;

double leftEncoderRadians = 0;
double rightEncoderRadians = 0;
double backEncoderRadians = 0;

double leftEncoderDistance = 0;
double rightEncoderDistance = 0;
double backEncoderDistance = 0;

double deltaTheta = 0;

double vectorComponentX = 0;
double vectorComponentY = 0;

double newVectorComponentX = 0;
double newVectorComponentY = 0;

double positionVector[2] = { 0, 0 };
double newVector[2] = { 0, 0 };


double x = 0;
double y = 0;
double r = 0;
double theta = 0;
double newX = 0;
double newY = 0;

void runPIDTask() {

	leftEncoderDegrees = leftEncoder.get_value();
	rightEncoderDegrees = rightEncoder.get_value();
	backEncoderDegrees = backEncoder.get_value();

	leftEncoderDegreesDifference = leftEncoderDegrees - previousLeftEncoderDegrees;
	rightEncoderDegreesDifference = rightEncoderDegrees - previousRightEncoderDegrees;
	backEncoderDegreesDifference = backEncoderDegrees - previousBackEncoderDegrees;

	previousLeftEncoderDegrees = leftEncoderDegrees;
	previousRightEncoderDegrees = rightEncoderDegrees;
	previousBackEncoderDegrees = backEncoderDegrees;

	leftEncoderDistance = leftEncoderDegreesDifference * M_PI / 180.0 * WHEEL_DIAMETER / 2;
	rightEncoderDistance = rightEncoderDegreesDifference * M_PI / 180.0 * WHEEL_DIAMETER / 2;
	backEncoderDistance = backEncoderDegreesDifference * M_PI / 180.0 * WHEEL_DIAMETER / 2;

	deltaTheta = (leftEncoderDistance - rightEncoderDistance) / (DISTANCE_TO_LEFT_ENCODER + DISTANCE_TO_RIGHT_ENCODER);

	x = 2 * sin(deltaTheta / 2) * (backEncoderDistance / deltaTheta + DISTANCE_TO_BACK_ENCODER);
	y = 2 * sin(deltaTheta / 2) * (rightEncoderDistance / deltaTheta + DISTANCE_TO_RIGHT_ENCODER);

	r = sqrt(pow(x, 2) + pow(y, 2));
	theta = atan(y / x);

	theta -= deltaTheta / 2;

	newX = r * cos(theta);
	newY = r * sin(theta);

	newVector[0] = newX;
	newVector[1] = newY;

	positionVector[0] = positionVector[0] + newVector[0];
	positionVector[1] = positionVector[1] + newVector[1];
}

void resetGlobal() {
	previousLeftEncoderDegrees = 0;
	previousRightEncoderDegrees = 0;
	previousBackEncoderDegrees = 0;

	leftEncoderDegrees = 0;
	rightEncoderDegrees = 0;
	backEncoderDegrees = 0;

	leftEncoderDegreesDifference = 0;
	rightEncoderDegreesDifference = 0;
	backEncoderDegreesDifference = 0;

	leftEncoderRadians = 0;
	rightEncoderRadians = 0;
	backEncoderRadians = 0;

	leftEncoderDistance = 0;
	rightEncoderDistance = 0;
	backEncoderDistance = 0;

	deltaTheta = 0;

	vectorComponentX = 0;
	vectorComponentY = 0;

	newVectorComponentX = 0;
	newVectorComponentY = 0;

	positionVector[0] = 0;
	positionVector[1] = 0;
	newVector[0] = 0;
	newVector[1] = 0;

	x = 0;
	y = 0;
	r = 0;
	theta = 0;
	newX = 0;
	newY = 0;
}

vector < vector<double> > generateLinearPath(double initX, double initY, double finalX, double finalY, double spacing) {
	//spacing is in inches between points
	vector < vector<double> > pointsList;
	double changeVector[2] = { finalX - initX, finalY - initY };
	double magnitude = sqrt(pow(changeVector[0], 2) + pow(changeVector[1], 2));
	double numPoints = ceil(magnitude / spacing);
	changeVector[0] = changeVector[0] * spacing / magnitude;
	changeVector[1] = changeVector[1] * spacing / magnitude;
	for (int i = 0; i < numPoints; i++) {
		vector<double> newVector{ initX + changeVector[0] * i, initY + changeVector[1] * i };
		pointsList.push_back(newVector);
	}
	vector<double> finalVector{ finalX, finalY };
	pointsList.push_back(finalVector);
	return pointsList;
}

vector <double> calculateDistance(vector < vector<double> > pointsList) {
	vector<double> distanceList;
	distanceList.push_back(0.0);
	for (int i = 1; i < pointsList.size(); i++) {
		distanceList.push_back(distanceList[i - 1] + sqrt(pow((pointsList[i][0] - pointsList[i - 1][0]), 2) + pow((pointsList[i][1] - pointsList[i - 1][1]), 2)));
	}
	return distanceList;
}

vector <double> calculateCurve(vector < vector<double> > pointsList) {
	vector<double> curveList;
	curveList.push_back(0.0);
	for (int i = 1; i < pointsList.size() - 1; i++) {
		double x1 = pointsList[i][0];
		double x2 = pointsList[i - 1][0];
		if (x1 == x2) {
			x1 += 0.001;
		}
		double x3 = pointsList[i + 1][0];
		double y1 = pointsList[i][1];
		double y2 = pointsList[i - 1][1];
		double y3 = pointsList[i + 1][1];
		double k1 = 0.5 * (pow(x1, 2) + pow(y1, 2) - pow(x2, 2) - pow(y2, 2)) / (x1 - x2);
		double k2 = (y1 - y2) / (x1 - x2);
		double b = 0.5 * (pow(x2, 2) - 2 * x2 * k1 + pow(y2, 2) - pow(x3, 2) + 2 * x2 * k1 - pow(y3, 2)) / (x3 * k2 - y3 + y2 - x2 * k2);
		double a = k1 - k2 * b;
		curveList.push_back(1 / sqrt(pow(x1 - a, 2) + pow(y1 - b, 2)));
	}
	curveList.push_back(0.0);
	return curveList;
}

vector < vector<double> > smooth(vector < vector<double> > pointsList, double b) {
	//b should be a value between 0.75 and 0.98
	vector < vector<double> > newPointsList = pointsList;
	double a = 1 - b;
	double tolerance = 0.001;
	double change = tolerance;
	while (change >= tolerance) {
		change = 0.0;
		for (int i = 1; i < pointsList.size() - 1; i++) {
			for (int j = 0; j < pointsList[i].size(); j++) {
				double aux = newPointsList[i][j];
				newPointsList[i][j] += a * (pointsList[i][j] - newPointsList[i][j]) + b *
					(newPointsList[i - 1][j] + newPointsList[i + 1][j] - (2.0 * newPointsList[i][j]));
				change += abs(aux - newPointsList[i][j]);
			}
		}
	}
	return newPointsList;
}

vector <double> calculateVelocity(vector < vector<double> > pointsList, vector <double> curveList, double maxVelocity, double maxAccel, double turnConstant) {
	//turnConstant should be between 1.0 and 5.0
	vector<double> maxVelList;
	for (int i = 0; i < curveList.size(); i++) {
		if (curveList[i] == 0.0) {
			curveList[i] = 0.001;
		}
		maxVelList.push_back(min(maxVelocity, (turnConstant / curveList[i])));
	}

	vector<double> targetVelList;
	targetVelList.push_back(0.0);
	double prevVel = 0.0;
	for (int i = 1; i < maxVelList.size(); i++) {
		prevVel = sqrt(pow(prevVel, 2) + 2 * maxAccel * sqrt(pow((pointsList[i][0] - pointsList[i - 1][0]), 2) + pow((pointsList[i][1] - pointsList[i - 1][1]), 2)));
		targetVelList.push_back(prevVel);
	}


	vector<double> velList(maxVelList.size(), 0.0);
	double previousVel = 0.0;
	for (int i = maxVelList.size() - 2; i <= 0; i--) {
		double distance = sqrt(pow((pointsList[i + 1][0] - pointsList[i][0]), 2) + pow((pointsList[i + 1][1] - pointsList[i][1]), 2));
		previousVel = min(targetVelList[i], sqrt(pow(previousVel, 2) + 2 * maxAccel * distance));
		velList[i] = previousVel;
	}
	return velList;
}

double dot(vector <double> a, vector <double> b) {
	return a[0] * b[0] + a[1] * b[1];
}

void PIDMove(vector < vector<double> > initPoints, double spacing, double smoothVal, double maxVelocity, double maxAccel, double turnConstant, double radius, double lookAheadPointsNum) {
	//spacing is in inches between points
	//smoothVal should be a value between 0.75 and 0.98
	//turnConstant should be between 1.0 and 5.0
	//radius is look ahead distance for path prediction
	//lookAheadPointsNum is the number of points to look ahead
	vector < vector<double> > pointsList;
	if (initPoints.size() == 0) {
		return;
	}
	else if (initPoints.size() == 1) {
		pointsList = generateLinearPath(positionVector[0], positionVector[1], initPoints[0][0], initPoints[0][1], spacing);
	}
	else {
		pointsList = generateLinearPath(initPoints[0][0], initPoints[0][1], initPoints[1][0], initPoints[1][1], spacing);
		if (initPoints.size() > 2) {
			for (int i = 1; i < initPoints.size() - 1; i++) {
				vector < vector<double> > pointsList2 = generateLinearPath(initPoints[i][0], initPoints[i][1], initPoints[i + 1][0], initPoints[i + 1][1], spacing);
				pointsList.insert(pointsList.end(), pointsList2.begin(), pointsList2.end());
			}
			pointsList = smooth(pointsList, smoothVal);
		}
	}
	vector <double> distanceList = calculateDistance(pointsList);
	vector <double> curveList = calculateCurve(pointsList);
	vector <double> velList = calculateVelocity(pointsList, curveList, maxVelocity, maxAccel, turnConstant);
	int closestPoint = 1;
	bool running = true;
	while (running) {
		double x = positionVector[0];
		double y = positionVector[1];
		vector<double> lookAheadPoint;
		double smallestDistance = sqrt(pow((pointsList[closestPoint][0] - x), 2) + pow((pointsList[closestPoint][1] - y), 2));
		if (closestPoint != pointsList.size() - lookAheadPointsNum) {
			for (int i = closestPoint + 1; i++; i < pointsList.size()) {
				double newDistance = sqrt(pow((pointsList[i][0] - x), 2) + pow((pointsList[i][1] - y), 2));
				if (smallestDistance > newDistance) {
					smallestDistance = newDistance;
					closestPoint = i;
				}
			}
			vector<double> E = pointsList[closestPoint];
			vector<double> L = pointsList[closestPoint + lookAheadPointsNum];
			vector<double> C = { x, y };
			vector<double> d = {L[0] - E[0], L[1] - E[1] };
			vector<double> f = { E[0] - C[0], E[1] - C[1] };
			double a = dot(d, d);
			double b = 2 * dot(f,d);
			double c = dot(f,f) - r * r;
			double discriminant = b * b - 4 * a * c;
			if (discriminant < 0) {
				// no intersection
			}
			else {
				double t1 = (-b - sqrt(discriminant)) / (2 * a);
				double t2 = (-b + sqrt(discriminant)) / (2 * a);
				if (t1 >= 0 && t1 <= 1) {
					lookAheadPoint = {E[0] + t1*d[0], E[1] + t1 * d[1] };
				}
				else if (t2 >= 0 && t2 <= 1) {
					lookAheadPoint = { E[0] + t2 * d[0], E[1] + t2 * d[1] };
				}
				else {
					
				}
			}

		}


	}
}

void autonomous() {
	resetGlobal();
	leftFrontMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	leftBackMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	rightFrontMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	rightBackMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);

	leftEncoder.reset();
	rightEncoder.reset();
	backEncoder.reset();

	pros::Task runPID(runPIDTask, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "PID Task");

}





/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor left_mtr(1);
	pros::Motor right_mtr(2);

	/*while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
						 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
						 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

		left_mtr = left;
		right_mtr = right;
		pros::delay(20);
	}*/
}
