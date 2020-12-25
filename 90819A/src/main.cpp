#include "main.h"

using namespace std;

#define _USE_MATH_DEFINES


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	//Calibrate inertial sensor
	imuLeft.reset();
	imuRight.reset();
	int time = pros::millis();
	int iter = 0;
	while (imuLeft.is_calibrating() || imuRight.is_calibrating())
	{
		printf("IMU calibrating... %d\n", iter);
		iter += 10;
		pros::delay(10);
	}
	//Should print about 2000 ms
	printf("IMU is done calibrating (took %d ms)\n", iter - time);
	displayInit(5);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled()
{
	//Reset position to (0,0,0)
	position.resetGlobal();
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize()
{
	//Show auton selection screen with default set as programming skills
	//displayInit(5);
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
void autonomous()
{
	//Reset position to (0,0,0)
	position.resetGlobal();

	// printf("here\n");
	//Set brake modes for all motors
	leftFrontMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	leftBackMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	rightFrontMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	rightBackMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	lowerStack.set_brake_mode(MOTOR_BRAKE_HOLD);
	upperStack.set_brake_mode(MOTOR_BRAKE_HOLD);
	intakeMotorLeft.set_brake_mode(MOTOR_BRAKE_BRAKE);
	intakeMotorRight.set_brake_mode(MOTOR_BRAKE_BRAKE);

	//Reset encoder values
	leftEncoder.reset();
	rightEncoder.reset();
	backEncoder.reset();

	//Run auton according to selection screen
	switch (getAutonCode())
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		//Reference to autons/progSkills.cpp
		runProgSkills();
		break;
	case 6:
		break;
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
void opcontrol()
{
	//Reference to driveControl.cpp
	driveControl();
}