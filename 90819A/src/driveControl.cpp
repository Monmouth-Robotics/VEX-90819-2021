#include "driveControl.h"


// Variables to control states of buttons
bool r1Pressed = false;
bool r2Pressed = false;
bool l1Pressed = false;
bool l2Pressed = false;
bool rightArrowPressed = false;
bool rightArrowActive = false;
bool topArrowPressed = false;
bool topArrowActive = false;


/**
 * Assigns motor speeds according to parameters:
 * motorSpeed: forward or backward speeds
 * turnSpeed: speed for rotating about the robot
 * strafeSpeed: speed for moving left and right
 */
void moveDrive(int motorSpeed, int turnSpeed, int strafeSpeed)
{

	if (abs(motorSpeed) > 20 && abs(turnSpeed) > 20 && abs(strafeSpeed) > 20)
	{
		leftFrontMotor = motorSpeed + turnSpeed + strafeSpeed;
		leftBackMotor = motorSpeed + turnSpeed - strafeSpeed;
		rightFrontMotor = motorSpeed - turnSpeed - strafeSpeed;
		rightBackMotor = motorSpeed - turnSpeed + strafeSpeed;
	}
	else if (abs(motorSpeed) > 20 && abs(turnSpeed) > 20)
	{
		leftFrontMotor = motorSpeed + turnSpeed;
		leftBackMotor = motorSpeed + turnSpeed;
		rightFrontMotor = motorSpeed - turnSpeed;
		rightBackMotor = motorSpeed - turnSpeed;
	}
	else if (abs(motorSpeed) > 20 && abs(strafeSpeed) > 20)
	{
		leftFrontMotor = motorSpeed + strafeSpeed;
		leftBackMotor = motorSpeed - strafeSpeed;
		rightFrontMotor = motorSpeed - strafeSpeed;
		rightBackMotor = motorSpeed + strafeSpeed;
	}
	else if (abs(turnSpeed) > 20 && abs(strafeSpeed) > 20)
	{
		leftFrontMotor = strafeSpeed + turnSpeed;
		leftBackMotor = -strafeSpeed + turnSpeed;
		rightFrontMotor = -strafeSpeed - turnSpeed;
		rightBackMotor = strafeSpeed - turnSpeed;
	}
	else if (abs(motorSpeed) > 20)
	{
		leftFrontMotor = motorSpeed;
		leftBackMotor = motorSpeed;
		rightFrontMotor = motorSpeed;
		rightBackMotor = motorSpeed;
	}
	else if (abs(turnSpeed) > 20)
	{
		leftFrontMotor = turnSpeed;
		leftBackMotor = turnSpeed;
		rightFrontMotor = -turnSpeed;
		rightBackMotor = -turnSpeed;
	}
	else if (abs(strafeSpeed) > 20)
	{
		leftFrontMotor = strafeSpeed;
		leftBackMotor = -strafeSpeed;
		rightFrontMotor = -strafeSpeed;
		rightBackMotor = strafeSpeed;
	}
	else
	{
		leftFrontMotor = 0;
		leftBackMotor = 0;
		rightFrontMotor = 0;
		rightBackMotor = 0;
	}
}

/**
 * Creates task to shoot one ball
 */
void shootOneBallFunction()
{
	pros::Task indexShootingController(indexerFunctions.shootOneBall, NULL, "Ball Shooter");
}

/**
 * Creates task to shoot two balls
 */
void shootTwoBallsFunction()
{
	pros::Task indexShootingController(indexerFunctions.shootTwoBalls, NULL, "Ball Shooter 2");
}

/**
 * Creates task to eject one ball
 */
void poopOneBallFunction(bool useTopRoller)
{
	pros::Task indexShootingController(indexerFunctions.poopOneBall, (void*)(useTopRoller), "Ball Pooper");
}

/**
 * Creates task to eject two balls
 */
void poopTwoBallsFunction(bool useTopRoller)
{
	pros::Task indexShootingController(indexerFunctions.poopTwoBalls, (void*)(useTopRoller), "Ball Pooper 2");
}

/**
 * Takes input from controller joysticks
 * Controls intakes and macro execution using button presses
 */
void driveControl()
{

	//Sets break modes for all motors
	leftFrontMotor.set_brake_mode(MOTOR_BRAKE_COAST);
	leftBackMotor.set_brake_mode(MOTOR_BRAKE_COAST);
	rightFrontMotor.set_brake_mode(MOTOR_BRAKE_COAST);
	rightBackMotor.set_brake_mode(MOTOR_BRAKE_COAST);
	lowerStack.set_brake_mode(MOTOR_BRAKE_BRAKE);
	upperStack.set_brake_mode(MOTOR_BRAKE_BRAKE);
	intakeMotorRight.set_brake_mode(MOTOR_BRAKE_BRAKE);
	intakeMotorLeft.set_brake_mode(MOTOR_BRAKE_BRAKE);

	while (true)
	{
		//Gets input from controller joysticks
		int motorSpeed = controller.get_analog(ANALOG_LEFT_Y);
		int strafeSpeed = controller.get_analog(ANALOG_LEFT_X);
		int turnSpeed = controller.get_analog(ANALOG_RIGHT_X);

		if (turnSpeed > 100)
			turnSpeed = 127;
		else if (turnSpeed < -100)
			turnSpeed = -127;

		moveDrive(motorSpeed, turnSpeed, strafeSpeed);

		//Control intakes
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

		//Controls shooting two balls
		if (controller.get_digital(DIGITAL_R2))
		{
			r2Pressed = true;
		}
		else if (r2Pressed) {
			shootTwoBallsFunction();
			r2Pressed = false;
		}

		//Controls shooting one ball
		else if (controller.get_digital(DIGITAL_R1))
		{
			r1Pressed = true;
		}
		else if (r1Pressed) {
			shootOneBallFunction();
			r1Pressed = false;
		}

		//Controls ejecting two balls
		if (controller.get_digital(DIGITAL_L2))
		{
			l2Pressed = true;
		}
		else if (l2Pressed) {
			poopTwoBallsFunction(!(controller.get_digital(DIGITAL_LEFT)));
			l2Pressed = false;
		}

		//Controls ejecting one ball
		else if (controller.get_digital(DIGITAL_L1))
		{
			l1Pressed = true;
		}

		else if (l1Pressed) {
			poopOneBallFunction(!(controller.get_digital(DIGITAL_LEFT)));
			l1Pressed = false;
		}

		if (controller.get_digital(DIGITAL_RIGHT)) {
			rightArrowPressed = true;
		}
		else if (rightArrowPressed) {
			if (rightArrowActive) {
				indexer.toggleBottom(false);
				indexer.toggleTop(false);
				rightArrowActive = false;
			}
			else {
				indexer.toggleBottom(true);
				indexer.toggleTop(true);
				upperStack = -127;
				lowerStack = -127;
				topArrowActive = false;
				rightArrowActive = true;
			}
			rightArrowPressed = false;
		}
		else if (controller.get_digital(DIGITAL_UP)) {
			topArrowPressed = true;
		}
		else if (topArrowPressed) {
			if (topArrowActive) {
				indexer.toggleBottom(false);
				indexer.toggleTop(false);
				topArrowActive = false;
			}
			else {
				indexer.toggleBottom(true);
				lowerStack = -127;
				rightArrowActive = false;
				topArrowActive = true;
			}
			topArrowPressed = false;
		}

		pros::delay(10);
	}
}