#include "main.h"
#include <cmath>

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
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

 
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
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


void autonomous() {
	
	double WHEEL_DIAMETER = 4; //inches
	double DISTANCE_TO_LEFT_ENCODER = 7.25; //inches
	double DISTANCE_TO_RIGHT_ENCODER = 7.25; //inches
	double DISTANCE_TO_BACK_ENCODER = 5.5; //inches
	
	leftFrontMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	leftBackMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	rightFrontMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	rightBackMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);

	leftEncoder.reset();
	rightEncoder.reset();
	backEncoder.reset();

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

	double positionVector[2] = {0, 0};
	double newVector[2] = {0, 0};

	double x = 0;
	double y = 0;
	double r = 0;
	double theta = 0;
	double newX = 0;
	double newY = 0;

	while (true){

		leftEncoderDegrees = leftEncoder.get_value();
		rightEncoderDegrees = rightEncoder.get_value();
		backEncoderDegrees = backEncoder.get_value();

		leftEncoderDegreesDifference = leftEncoderDegrees - previousLeftEncoderDegrees;
		rightEncoderDegreesDifference = rightEncoderDegrees - previousRightEncoderDegrees;
		backEncoderDegreesDifference = backEncoderDegrees - previousBackEncoderDegrees;

		previousLeftEncoderDegrees = leftEncoderDegrees;
		previousRightEncoderDegrees = rightEncoderDegrees;
		previousBackEncoderDegrees = backEncoderDegrees;

		leftEncoderDistance = leftEncoderDegreesDifference * M_PI / 180.0 * WHEEL_DIAMETER/2;
		rightEncoderDistance = rightEncoderDegreesDifference * M_PI / 180.0 * WHEEL_DIAMETER/2;
		backEncoderDistance = backEncoderDegreesDifference * M_PI / 180.0 * WHEEL_DIAMETER/2;

		deltaTheta =  (leftEncoderDistance - rightEncoderDistance) / (DISTANCE_TO_LEFT_ENCODER + DISTANCE_TO_RIGHT_ENCODER);

		x = 2 * sin(deltaTheta/2) * (backEncoderDistance / deltaTheta + DISTANCE_TO_BACK_ENCODER);
		y = 2 * sin(deltaTheta/2) * (rightEncoderDistance / deltaTheta + DISTANCE_TO_RIGHT_ENCODER);

		r = sqrt(pow(x, 2) + pow(y, 2));
		theta = atan(y/x);

		theta -= deltaTheta/2;

		newX = r * cos(theta);
		newY = r * sin(theta);

		newVector[0] = newX;
		newVector[1] = newY;		
		
		positionVector[0] = positionVector[0] + newVector[0];
		positionVector[1] = positionVector[1] + newVector[1];
	}
	
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
