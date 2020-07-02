#include "main.h"
#include <cmath>
#include <ctime>
#include <iostream> 
#include <list> 
#include <iterator> 
using namespace std;

#define _USE_MATH_DEFINES

pros::Controller controller(CONTROLLER_MASTER);

//pros::Motor leftFrontMotor(14, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
//pros::Motor leftBackMotor(11, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
//pros::Motor rightFrontMotor(17, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
//pros::Motor rightBackMotor(20, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);

pros::Motor leftFrontMotor(9, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor leftBackMotor(21, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor rightFrontMotor(6, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
pros::Motor rightBackMotor(10, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);

pros::Motor lowerStack(7, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor upperStack(11, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor intakeMotorLeft(1, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor intakeMotorRight(12, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);

pros::ADIEncoder leftEncoder('C', 'D', true);
pros::ADIEncoder rightEncoder('G', 'H', true);
pros::ADIEncoder backEncoder('A', 'B', false);

time_t currentTime;
lv_obj_t* text = lv_label_create(lv_scr_act(), NULL);
int autonCode = 5;

void setAutonState() {
	if (autonCode == 1)
	{
		lv_label_set_text(text, "Current State: Blue Easy Autonomous");
	}
	else if (autonCode == 2)
	{
		lv_label_set_text(text, "Current State: Blue Hard Autonomous");
	}
	else if (autonCode == 3)
	{
		lv_label_set_text(text, "Current State: Red Easy Autonomous");
	}

	else if (autonCode == 4)
	{
		lv_label_set_text(text, "Current State: Red Hard Autonomous");
	}
	else if (autonCode == 5)
	{
		lv_label_set_text(text, "Current State: Programming Skills");
	}
	else if (autonCode == 6)
	{
		lv_label_set_text(text, "Current State: Driver Skills");
	}
}

lv_res_t btn1_action(lv_obj_t* btn)
{
	autonCode = 1;
	setAutonState();
	return LV_RES_OK;
}

lv_res_t btn2_action(lv_obj_t* btn)
{
	autonCode = 2;
	setAutonState();
	return LV_RES_OK;
}

lv_res_t btn3_action(lv_obj_t* btn)
{
	autonCode = 3;
	setAutonState();
	return LV_RES_OK;
}

lv_res_t btn4_action(lv_obj_t* btn)
{
	autonCode = 4;
	setAutonState();
	return LV_RES_OK;
}

lv_res_t btn5_action(lv_obj_t* btn)
{
	autonCode = 5;
	setAutonState();
	return LV_RES_OK;
}

lv_res_t btn6_action(lv_obj_t* btn)
{
	autonCode = 6;
	setAutonState();
	return LV_RES_OK;
}


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
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
void competition_initialize() {
	pros::delay(200);
	lv_obj_t* btn1 = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_pos(btn1, 100, 20);
	lv_obj_set_size(btn1, 100, 50);
	lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn1_action);

	lv_obj_t* label1 = lv_label_create(btn1, NULL);
	lv_label_set_text(label1, "Blue Easy");

	lv_obj_t* btn2 = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_pos(btn2, 100, 100);
	lv_obj_set_size(btn2, 100, 50);
	lv_btn_set_action(btn2, LV_BTN_ACTION_CLICK, btn2_action);

	lv_obj_t* label2 = lv_label_create(btn2, NULL);
	lv_label_set_text(label2, "Blue Hard");

	lv_obj_t* btn3 = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_pos(btn3, 300, 20);
	lv_obj_set_size(btn3, 100, 50);
	lv_btn_set_action(btn3, LV_BTN_ACTION_CLICK, btn3_action);

	lv_obj_t* label3 = lv_label_create(btn3, NULL);
	lv_label_set_text(label3, "Red Easy");

	lv_obj_t* btn4 = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_pos(btn4, 300, 100);
	lv_obj_set_size(btn4, 100, 50);
	lv_btn_set_action(btn4, LV_BTN_ACTION_CLICK, btn4_action);

	lv_obj_t* label4 = lv_label_create(btn4, NULL);
	lv_label_set_text(label4, "Red Hard");

	lv_obj_t* btn5 = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_pos(btn5, 50, 200);
	lv_obj_set_size(btn5, 180, 50);
	lv_btn_set_action(btn5, LV_BTN_ACTION_CLICK, btn5_action);

	lv_obj_t* label5 = lv_label_create(btn5, NULL);
	lv_label_set_text(label5, "Programming Skills");

	lv_obj_t* btn6 = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_pos(btn6, 275, 200);
	lv_obj_set_size(btn6, 150, 50);
	lv_btn_set_action(btn6, LV_BTN_ACTION_CLICK, btn6_action);

	lv_obj_t* label6 = lv_label_create(btn6, NULL);
	lv_label_set_text(label6, "Driver Skills");

	lv_obj_set_pos(text, 0, 0); /*Set its position*/

	setAutonState();
}

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
double WHEEL_DIAMETER = 2.75;
double DISTANCE_TO_LEFT_ENCODER = 4.725;
double DISTANCE_TO_RIGHT_ENCODER = 4.725;
double DISTANCE_TO_BACK_ENCODER = 5;

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
double polarTheta = 0;

vector<double> positionVector = { 0,0 };
vector<double> newVector = { 0,0 };


double x;
double y;
double r;
double theta;
double newX;
double newY;

int count2 = 0;

void runPositionTask() {

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

	theta -= deltaTheta;

	if (deltaTheta != 0) {
		x = 2 * sin(deltaTheta / 2) * (backEncoderDistance / deltaTheta + DISTANCE_TO_BACK_ENCODER);
		y = 2 * sin(deltaTheta / 2) * (rightEncoderDistance / deltaTheta + DISTANCE_TO_RIGHT_ENCODER);
	}	
	else {
		x = backEncoderDistance;
		y = rightEncoderDistance;
	}

	while (theta > M_PI*2) {
		theta -= M_PI * 2;
	}
	while (theta < 0) {
		theta += M_PI * 2;
	}

	//convert to polar, rotate by negative theta, convert back

	r = sqrt(x*x+y*y);
	if (x != 0) {
		polarTheta = atan(y / x);
		polarTheta -= theta;
	}

	newX = r * sin(polarTheta);
	newY = r * cos(polarTheta);

	if (x< 0)
	{
		newX *= -1;
	}
	if (y<0)
	{
		newY *= -1;
	}
	//newVector[0] = x;
	//newVector[1] = y;

	// positionVector[0] = positionVector[0] + newVector[0];
	// positionVector[1] = positionVector[1] + newVector[1];

	positionVector[0] = positionVector[0] + newX;
	positionVector[1] = positionVector[1] + newY;

	
	//printf("x-coordinate: %.3f\n", positionVector[0]);
	//printf("y-coordinate: %.3f\n", positionVector[1]);

	
	// printf("change in raw x: %.3f\n", x);
	// printf("change in raw y: %.3f\n", y);
	// printf("change in x: %.3f\n", newX);
	// printf("change in y: %.3f\n", newY);
	// printf("x: %.3f\n", positionVector[0]);
	// printf("y: %.3f\n", positionVector[1]);

	// pros::delay(10000);
	// runPositionTask();
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
	polarTheta = 0;

	positionVector[0] = 0;
	positionVector[1] = 0;
	newVector[0] = 0;
	newVector[1] = 0;

	x = 0;
	y = 0;
	r = 0;
	theta = M_PI/2;
	newX = 0;
	newY = 0;

	count2 = 0;

	leftEncoder.reset();
	rightEncoder.reset();
	backEncoder.reset();
}

vector < vector<double> > generateLinearPath(double initX, double initY, double finalX, double finalY, double spacing) {
	//spacing is in inches between points
	vector < vector<double> > pointsList;
	vector<double> changeVector = { finalX - initX, finalY - initY };
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
		double b = 0.5 * (pow(x2, 2) - 2 * x2 * k1 + pow(y2, 2) - pow(x3, 2) + 2 * x3 * k1 - pow(y3, 2)) / (x3 * k2 - y3 + y2 - x2 * k2);
		double a = k1 - k2 * b;
		curveList.push_back(1 / sqrt(pow(x1 - a, 2) + pow(y1 - b, 2)));
	}
	curveList.push_back(0.0);
	return curveList;
}

vector < vector<double> > smooth(vector < vector<double> > pointsList, double a, double b, double tolerance) {
	//b should be a value between 0.75 and 0.98
	vector < vector<double> > newPointsList = pointsList;
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

vector<double> findLookAheadPoint(double x, double y, vector < vector<double> > pointsList, int closestPoint, int lookAheadPointsNum) {
	vector<double> E = pointsList[closestPoint];
	vector<double> L = pointsList[closestPoint + lookAheadPointsNum];
	vector<double> C = { x, y };
	vector<double> d = { L[0] - E[0], L[1] - E[1] };
	vector<double> f = { E[0] - C[0], E[1] - C[1] };
	double a = dot(d, d);
	double b = 2 * dot(f, d);
	double c = dot(f, f) - r * r;
	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0) {
		// no intersection
	}
	else {
		double t1 = (-b - sqrt(discriminant)) / (2 * a);
		double t2 = (-b + sqrt(discriminant)) / (2 * a);
		if (t1 >= 0 && t1 <= 1) {
			return { E[0] + t1 * d[0], E[1] + t1 * d[1] };
		}
		else if (t2 >= 0 && t2 <= 1) {
			return { E[0] + t2 * d[0], E[1] + t2 * d[1] };
		}
		else {
			if (closestPoint != pointsList.size() - lookAheadPointsNum - 1) {
				return findLookAheadPoint(x, y, pointsList, closestPoint, lookAheadPointsNum + 1);
			}
			else {
				return pointsList[pointsList.size() - 1];
			}
		}
	}
}

double findCurvature(vector<double> lookAheadPoint, double Rx, double Ry) {
	double curvature = (2 * (lookAheadPoint[0] - Rx)) / pow(sqrt(pow((lookAheadPoint[0] - Rx), 2) + pow((lookAheadPoint[1] - Ry), 2)), 2);
	double angle = tanh((lookAheadPoint[1] - Ry) / (lookAheadPoint[0] - Rx));
	double Bx = Rx + cos(angle);
	double By = Ry + sin(angle);
	double sign = (sin(angle) * (lookAheadPoint[0] - Rx) - cos(angle) * (lookAheadPoint[1] - Ry)) / abs(sin(angle) * (lookAheadPoint[0] - Rx) - cos(angle) * (lookAheadPoint[1] - Ry));
	return curvature * sign;
}

vector<double> rateLimit(double velocity, double maxAccel, double prevVel) {
	double maxChange = (time(0) - currentTime) * maxAccel;
	double newVel = prevVel;
	double accel;
	if (-1 * maxChange > (velocity - newVel)) {
		newVel += -1 * maxChange;
		accel = -1 * maxChange;
	}
	else if (maxChange < (velocity - newVel)) {
		newVel += maxChange;
		accel = maxChange;
	}
	else {
		newVel += (velocity - newVel);
		accel = velocity - newVel;
	}
	currentTime = time(0);
	return { newVel, accel };
}

vector<double> findVelocities(double curvature, double trackWidth, double velocity, double maxAccel, vector<double> prevVel) {
	vector<double> leftVel = rateLimit(velocity, maxAccel, prevVel[0]);
	vector<double> rightVel = rateLimit(velocity, maxAccel, prevVel[1]);
	double newVel;
	double accel;
	if (rightVel[0] < leftVel[0]) {
		newVel = rightVel[0];
		accel = rightVel[1];
	}
	else {
		newVel = leftVel[0];
		accel = leftVel[1];
	}
	return { newVel * (2 + curvature * trackWidth) / 2,newVel * (2 - curvature * trackWidth) / 2, accel };
}

void move(vector < vector<double> > initPoints, double spacing, double smoothVal1, double smoothVal2, double smoothTolerance, double maxVelocity, double maxAccel, double turnConstant, int lookAheadPointsNum, double trackWidth, double Kv, double Ka, double Kp) {
	//initPoints are all the points in the motion, including start and end
	//spacing is in inches between points
	//smoothVal1 should be 1-smoothVal2
	//smoothVal2 should be a value between 0.75 and 0.98
	//maxVelocity is the highest speed the robot is allowed to reach during this movement
	//maxAccel is the highest acceleration the robot is allowed to encounter during this movement
	//turnConstant should be between 1.0 and 5.0
	//lookAheadPointsNum is the number of points to look ahead
	//smoothTolerance default is 0.001
	/*trackWidth is measured from the robot. Due to turning scrub,
	 *you want to use a track width a few inches larger than the real one.*/
	 /*start Kv at 1/maxVelocity and start all other constants at 0
	  *Tune Kv until the velocities match up
	  *Set Ka to 0.002
	  *Tune until accelerating and decelerating velocities are near accurate
	  *Start Kp at 0.01 and increase number to make more accurate
	  *Setting Kp too high will result in a jittery motion*/

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
			pointsList = smooth(pointsList, smoothVal1, smoothVal2, smoothTolerance);
		}
	}
	//vector <double> distanceList = calculateDistance(pointsList);
	vector <double> curveList = calculateCurve(pointsList);
	vector <double> velList = calculateVelocity(pointsList, curveList, maxVelocity, maxAccel, turnConstant);
	int closestPoint = 1;
	vector<double> velocities = { 0.0, 0.0 };
	currentTime = time(0);
	while (true) {
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
			lookAheadPoint = findLookAheadPoint(x, y, pointsList, closestPoint, lookAheadPointsNum);
		}
		else {
			lookAheadPoint = pointsList[pointsList.size() - 1];
		}
		if (closestPoint == pointsList.size() - 1) {
			break;
		}
		double curvature = findCurvature(lookAheadPoint, x, y);
		vector<double> velocities = findVelocities(curvature, trackWidth, velList[closestPoint], maxAccel, velocities);
		double leftFF = Kv * velocities[0] + Ka * (velocities[2]);
		double rightFF = Kv * velocities[1] + Ka * (velocities[2]);
		double leftFB = Kp * (velocities[0] - ((leftFrontMotor.get_actual_velocity() + leftBackMotor.get_actual_velocity()) / 2));
		double rightFB = Kp * (velocities[1] - ((rightFrontMotor.get_actual_velocity() + rightBackMotor.get_actual_velocity()) / 2));
		leftFrontMotor = leftFF + leftFB;
		leftBackMotor = leftFF + leftFB;
		rightFrontMotor = rightFF + rightFB;
		rightBackMotor = rightFF + rightFB;
	}
}

void pidTurn(double target, double maxVel, double thresholdError, double kP){
	
	while (abs(error) > thresholdError)
	{
		runPositionTask();
		double error = target - theta;
		power = kP * error
		if (power > maxVel)
			power = maxVel;
		if (power < -maxVel)
			power = -maxVel;
		leftBackMotor = -power;
		leftFrontMotor = -power;
		rightBackMotor = power;
		rightFrontMotor = power;
		pros::delay(10)
	}

	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightBackMotor = 0;
	rightFrontMotor = 0;
	
}

void pidStraight (double targetX, double targetY, double targetTheta, double maxVel, double thresholdError, double kP, double kPStraight)
{
	while abs(error) > thresholdError{
		double error = sqrt(pow(targetX - positionVector[0], 2) +  pow(targetY - positionVector[1], 2) * 1.0);
		power = kP * error
		if (power > maxVel)
			power = maxVel;
		if (power < -maxVel)
			power = -maxVel;
		double straightError = targetTheta - theta;
		powerChange = straightError * kPStraight;

		leftBackMotor = -power + powerChange;
		leftFrontMotor = -power + powerChange;
		rightBackMotor = power + powerChange;
		rightFrontMotor = power + powerChange;

		pros::delay(10)
	}

	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightBackMotor = 0;
	rightFrontMotor = 0;
}
void autonomous() {
	leftFrontMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	leftBackMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	rightFrontMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	rightBackMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);

	resetGlobal();

	pidTurn(M_PI, 80, 0.006, 110)
	pidTurn(2*M_PI, 80, 0.006, 110)

	pidStraight(0, 24.0, 0, 63, 0.006, 110, 110)
	// double target = M_PI;
	// double kP = 0.01;
	// double error = 99999999;
	// double power;
	// double threshold = 0.006;
	
	// while (error > threshold)
	// {
	// 	runPositionTask();
	// 	printf("theta: %.3f\n", theta*180/M_PI);
	// 	error = target - theta;
	// 	power = 11000*error *kP;
		
	// 	if (power > 63)
	// 		power = 63;
	// 	if (power < -63)
	// 		power = -63;

	// 	leftBackMotor = -power;
	// 	leftFrontMotor = -power;
	// 	rightBackMotor = power;
	// 	rightFrontMotor = power;
	// 	pros::delay(10);
	// }
	
	// leftBackMotor = 40;
	// leftFrontMotor = 40;
	// rightBackMotor = 40;
	// rightFrontMotor = 40;



	//pros::Task positionTask(runPositionTask, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Position Task");
	//move({ {0.0, 0.0},{10.0, 10.0}, {20.0,20.0} }, 1.0, 0.15, 0.85, 0.001, 10.0, 3.0, 3.0, 2, 15.0, 0.01, 0.002, 0.01);
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

void move2(float motorSpeed, float turnSpeed)
{	
	if (abs(motorSpeed) > 20 && abs(turnSpeed) > 20)
	{
		leftFrontMotor = motorSpeed + turnSpeed;
		leftBackMotor = motorSpeed + turnSpeed;
		rightFrontMotor = motorSpeed - turnSpeed;
		rightBackMotor = motorSpeed - turnSpeed;
	}

	// if only motorSpeed is beyond the minimum, just move
	else if (abs(motorSpeed) > 20)
	{
		leftFrontMotor = motorSpeed;
		leftBackMotor = motorSpeed;
		rightFrontMotor = motorSpeed;
		rightBackMotor = motorSpeed;
	}

	// if only turnSpeed is beyond the minimum, just turn
	else if (abs(turnSpeed) > 20)
	{
		leftFrontMotor = turnSpeed;
		leftBackMotor = turnSpeed;
		rightFrontMotor = -turnSpeed;
		rightBackMotor = -turnSpeed;
	}

	else
	{
		leftFrontMotor = 0;
		leftBackMotor = 0;
		rightFrontMotor = 0;
		rightBackMotor = 0;
	}
}

float exponential(float input, float output, float x)
{
	float base = pow((127 / output), (1 / (127 - input)));
	float a = output / (pow(base, input));

	return (a * (pow(base, abs(x))));
}

float driveInput = 25;
float driveOutput = 10;
float turnInput = 40;
float turnOutput = 10;
bool intakeMotor = true;

void opcontrol()
{


	// Break type for all motors
	leftFrontMotor.set_brake_mode(MOTOR_BRAKE_COAST);
	leftBackMotor.set_brake_mode(MOTOR_BRAKE_COAST);
	rightFrontMotor.set_brake_mode(MOTOR_BRAKE_COAST);
	rightBackMotor.set_brake_mode(MOTOR_BRAKE_COAST);
	//lowerStack.set_brake_mode(MOTOR_BRAKE_BRAKE);
	//upperStack.set_brake_mode(MOTOR_BRAKE_BRAKE);
	//intakeMotorRight.set_brake_mode(MOTOR_BRAKE_BRAKE);
	//intakeMotorLeft.set_brake_mode(MOTOR_BRAKE_BRAKE);

	/*secondaryLiftMotor.move_relative(50, 70);
	while (!(secondaryLiftMotor.get_position() < 52) && !(secondaryLiftMotor.get_position() > 48)) {
		pros::delay(2);
	}*/

	while (true)
	{
		float turnSpeed;

		int motorSpeedRaw = controller.get_analog(ANALOG_LEFT_Y);
		int turnSpeedRaw = controller.get_analog(ANALOG_RIGHT_X);

		float motorSpeed = (motorSpeedRaw / abs(motorSpeedRaw) * (exponential(driveInput, driveOutput, motorSpeedRaw)));
		if (turnSpeedRaw > 100)
			turnSpeed = 127;
		else if (turnSpeedRaw < -100)
			turnSpeed = -127;
		else
			turnSpeed = (turnSpeedRaw / abs(turnSpeedRaw) * (exponential(turnInput, turnOutput, turnSpeedRaw)) * 0.5);


		move2(motorSpeed, turnSpeed);

		// fights gravity so lift doesn't fall
		/*if (controller.get_digital(DIGITAL_B)) {
			BPressed = true;
		}
		else if (BPressed) {
			intakeMotor = !intakeMotor;
			BPressed = false;
		}
		else
		{
			liftMotorLeft = 5;
			liftMotorRight = 5;
		}*/

		if (controller.get_digital(DIGITAL_B))
		{
			intakeMotorLeft = 0;
			intakeMotorRight = 0;
		}


		else if (controller.get_digital(DIGITAL_A))
		{
			intakeMotorLeft = 127;
			intakeMotorRight = 127;
		}
		else if (controller.get_digital(DIGITAL_Y))
		{
			intakeMotorLeft = -127;
			intakeMotorRight = -127;
		}

		else if (controller.get_digital(DIGITAL_X))
		{
			upperStack = -127;
			lowerStack = -127;
		}

		if (controller.get_digital(DIGITAL_L1))
		{
			upperStack = 127;
			/*char val[100];
			sprintf(val, "Lift Motor: %f", liftMotor.get_position());
			lv_label_set_text(text, val);*/
		}

		else if (controller.get_digital(DIGITAL_L2))
		{
			upperStack = 0;

		}

		if (controller.get_digital(DIGITAL_R1))
		{
			lowerStack = 127;
			/*char val[100];
			sprintf(val, "Lift Motor: %f", liftMotor.get_position());
			lv_label_set_text(text, val);*/
		}

		else if (controller.get_digital(DIGITAL_R2))
		{
			lowerStack = 0;

		}

		if (controller.get_digital(DIGITAL_LEFT))
		{
			lowerStack = -127;
			/*char val[100];
			sprintf(val, "Lift Motor: %f", liftMotor.get_position());
			lv_label_set_text(text, val);*/
		}


		/*if (controller.get_digital(DIGITAL_R1))
		{
			deploy(chassis, profileController, trayController, liftController);
		}*/

		pros::delay(10);
	}
}
