#include "main.h"
#include <vector>

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

using namespace std;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button()
{
	static bool pressed = false;
	pressed = !pressed;
	if (pressed)
	{
		pros::lcd::set_text(2, "I was pressed!");
	}
	else
	{
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
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
void autonomous() {}

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
void opcontrol()
{
	pros::Controller controller(CONTROLLER_MASTER);

	pros::Motor intakeMotorLeft(4, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
	pros::Motor intakeMotorRight(7, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);

	// pros::Motor lowerStack(1, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
	// pros::Motor upperStack(10, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);

	// while (true)
	// {
	// 	upperStack = 127;
	// 	lowerStack = 127;
	// 	if (controller.get_digital(DIGITAL_A))
	// 	{
	// 		intakeMotorLeft = 127;
	// 		intakeMotorRight = 127;
	// 	}

	// 	else
	// 	{
	// 		intakeMotorLeft = 0;
	// 		intakeMotorRight = 0;
	// 	}
	// 	pros::delay(10);
	// }

	pros::ADIEncoder leftEncoder('A', 'B', true);
	pros::ADIEncoder rightEncoder('G', 'H', true);
	pros::ADIEncoder backEncoder('E', 'F', true);

	pros::ADIAnalogIn lineSensor('D');

	double WHEEL_DIAMETER = 2.75;
	double DISTANCE_TO_LEFT_ENCODER = 5.375;
	double DISTANCE_TO_RIGHT_ENCODER = 5.375;
	double DISTANCE_TO_BACK_ENCODER = 6.0625;

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

	vector<double> positionVector = {0, 0};
	vector<double> newVector = {0, 0};

	double x;
	double y;
	double r;
	double theta;
	double newX;
	double newY;
	double thetaM;

	int count2 = 0;
	while (true)
	{

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

		//printf("Left: %.3f\n", leftEncoderDegrees * M_PI / 180.0 * WHEEL_DIAMETER/2);
		//printf("right: %.3f\n", rightEncoderDegrees * M_PI / 180.0 * WHEEL_DIAMETER/2);
		//printf("Back: %.3f\n", backEncoderDegrees * M_PI / 180.0 * WHEEL_DIAMETER/2);

		deltaTheta = (leftEncoderDistance - rightEncoderDistance) / (DISTANCE_TO_LEFT_ENCODER + DISTANCE_TO_RIGHT_ENCODER);

		theta += deltaTheta;

		if (deltaTheta != 0)
		{
			x = 2 * sin(deltaTheta / 2) * (backEncoderDistance / deltaTheta + DISTANCE_TO_BACK_ENCODER);
			y = 2 * sin(deltaTheta / 2) * (rightEncoderDistance / deltaTheta + DISTANCE_TO_RIGHT_ENCODER);

			// printf("Offset: %f\n", offset);
		}
		else
		{
			x = backEncoderDistance;
			y = rightEncoderDistance;
		}

		while (theta > M_PI * 2)
		{
			theta -= M_PI * 2;
		}
		while (theta < 0)
		{
			theta += M_PI * 2;
		}

		//rotate by negative theta, convert back

		thetaM = theta - deltaTheta / 2;

		newX = x * cos(-thetaM) - y * sin(-thetaM);
		newY = y * cos(-thetaM) + x * sin(-thetaM);

		// offset = abs(atan2f(y, x));

		positionVector[0] = positionVector[0] + newX;
		positionVector[1] = positionVector[1] + newY;

		//printf("x-coordinate: %.3f\n", positionVector[0]);
		//printf("y-coordinate: %.3f\n", positionVector[1]);
		//printf("change in raw x: %.3f\n", x);
		//printf("change in raw y: %.3f\n", y);
		//printf("change in x: %.3f\n", newX);
		//printf("change in y: %.3f\n", newY);
		printf("x: %.3f\n", positionVector[0]);
		printf("y: %.3f\n", positionVector[1]);
		printf("theta: %.3f\n", theta * 180 / M_PI);
		printf("lineSensor: %d", lineSensor.get_value());

			if (controller.get_digital(DIGITAL_A))
		{
			intakeMotorLeft = 127;
			intakeMotorRight = 127;
		}

		else
		{
			intakeMotorLeft = 0;
			intakeMotorRight = 0;
		}
		// printf("line Sensor: %d", lineSensor.get_value());
		pros::delay(10);
	}
	// double WHEEL_DIAMETER = 2.75;
	// double DISTANCE_TO_LEFT_ENCODER = 5.375;
	// double DISTANCE_TO_RIGHT_ENCODER = 5.375;
	// double DISTANCE_TO_BACK_ENCODER = 6.0625;

	// double previousLeftEncoderDegrees = 0;
	// double previousRightEncoderDegrees = 0;
	// double previousBackEncoderDegrees = 0;

	// double leftEncoderDegrees = 0;
	// double rightEncoderDegrees = 0;
	// double backEncoderDegrees = 0;

	// double leftEncoderDegreesDifference = 0;
	// double rightEncoderDegreesDifference = 0;
	// double backEncoderDegreesDifference = 0;

	// double leftEncoderRadians = 0;
	// double rightEncoderRadians = 0;
	// double backEncoderRadians = 0;

	// double leftEncoderDistance = 0;
	// double rightEncoderDistance = 0;
	// double backEncoderDistance = 0;

	// double deltaTheta = 0;
	// double polarTheta = 0;

	// vector<double> positionVector = {0, 0};
	// vector<double> newVector = {0, 0};

	// float x = 0;
	// float y = 0;
	// float a = 0;

	// // double x;
	// // double y;
	// double r;
	// double theta = 0;
	// double newX;
	// double newY;
	// double thetaM;

	// int count2 = 0;

	// // leftEncoder.reset();
	// // rightEncoder.reset();
	// // backEncoder.reset();

	// while (true)
	// {
	// 	leftEncoderDegrees = leftEncoder.get_value();
	// 	rightEncoderDegrees = rightEncoder.get_value();
	// 	backEncoderDegrees = backEncoder.get_value();

	// 	leftEncoderDegreesDifference = leftEncoderDegrees - previousLeftEncoderDegrees;
	// 	rightEncoderDegreesDifference = rightEncoderDegrees - previousRightEncoderDegrees;
	// 	backEncoderDegreesDifference = backEncoderDegrees - previousBackEncoderDegrees;

	// 	previousLeftEncoderDegrees = leftEncoderDegrees;
	// 	previousRightEncoderDegrees = rightEncoderDegrees;
	// 	previousBackEncoderDegrees = backEncoderDegrees;

	// 	leftEncoderDistance = leftEncoderDegreesDifference * M_PI / 180.0 * WHEEL_DIAMETER / 2;
	// 	rightEncoderDistance = rightEncoderDegreesDifference * M_PI / 180.0 * WHEEL_DIAMETER / 2;
	// 	backEncoderDistance = backEncoderDegreesDifference * M_PI / 180.0 * WHEEL_DIAMETER / 2;

	// 	float L = leftEncoderDistance;   // The amount the left side of the robot moved
	// 	float R = rightEncoderDistance; // The amount the right side of the robot moved
	// 	float S = backEncoderDistance;	   // The amount the back side of the robot moved

	// 	// Update the last values
	// 	// float leftLst = left;
	// 	// float rightLst = right;
	// 	// float backLst = back;

	// 	float h;											 // The hypotenuse of the triangle formed by the middle of the robot on the starting position and ending position and the middle of the circle it travels around
	// 	float i;											 // Half on the angle that I've traveled
	// 	float h2;											 // The same as h but using the back instead of the side wheels
	// 	float a = (L - R) / (DISTANCE_TO_LEFT_ENCODER + DISTANCE_TO_RIGHT_ENCODER); // The angle that I've traveled
	// 	if (a)
	// 	{
	// 		float r = R / a; // The radius of the circle the robot travel's around with the right side of the robot
	// 		i = a / 2.0;
	// 		float sinI = sin(i);
	// 		h = ((r + DISTANCE_TO_RIGHT_ENCODER) * sinI) * 2.0;

	// 		float r2 = S / a; // The radius of the circle the robot travel's around with the back of the robot
	// 		h2 = ((r2 + DISTANCE_TO_BACK_ENCODER) * sinI) * 2.0;
	// 	}
	// 	else
	// 	{
	// 		h = R;
	// 		i = 0;

	// 		h2 = S;
	// 	}
	// 	float p = i + theta; // The global ending angle of the robot
	// 	float cosP = cos(p);
	// 	float sinP = sin(p);

	// 	// Update the global position
	// 	y += h * cosP;
	// 	x += h * sinP;

	// 	y += h2 * -sinP; // -sin(x) = sin(-x)
	// 	x += h2 * cosP;  // cos(x) = cos(-x)

	// 	theta += a;

	// 	printf("(%.3f, %.3f, %.3f)\n", x, y, theta);
	// 	pros::delay(10);
	// }
}
