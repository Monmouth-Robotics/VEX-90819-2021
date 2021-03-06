#include "driveControl.h"


// Variables to control states of buttons
bool r1Pressed = false;
bool r2Pressed = false;
bool l1Pressed = false;
bool l2Pressed = false;
bool xPressed = false;
bool rightArrowPressed = false;
bool rightArrowActive = false;
bool topArrowPressed = false;
bool topArrowActive = false;
bool shiftKeyPressed = false;


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
	else if (abs(motorSpeed) > 30 && abs(turnSpeed) > 30)
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
// void shootOneBallFunction()
// {
// 	pros::Task shootOneBallController(ShootController().shootOneBall, NULL, "Ball Shooter");
// }

/**
 * Creates task to shoot two balls
 */
// void shootTwoBallsFunction()
// {
// 	pros::Task shootTwoBallsController(ShootController().shootTwoBalls, NULL, "Ball Shooter 2");
// }

/**
 * Creates task to shoot powerful
 */
// void shootPowerfulFunction()
// {
// 	pros::Task shootPowerfulController(ShootController().shootPowerful, NULL, "Shoot Powerful");
// }

/**
 * Creates task to eject one ball
 */
// void ejectOneBallFunction(bool useTopRoller)
// {
// 	pros::Task ejectOneBallController(EjectController()
// 		.setTopRoller(useTopRoller)
// 		.ejectOneBall, NULL, "Ball Ejecter");
// }

// /**
//  * Creates task to eject two balls
//  */
// void ejectTwoBallsFunction(bool useTopRoller)
// {
// 	pros::Task ejectTwoBallsController(EjectController()
// 		.setTopRoller(useTopRoller)
// 		.ejectTwoBalls, NULL, "Ball Ejecter 2");
// }

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
	lowerStack.set_brake_mode(MOTOR_BRAKE_HOLD);
	upperStack.set_brake_mode(MOTOR_BRAKE_HOLD);
	intakeMotorRight.set_brake_mode(MOTOR_BRAKE_BRAKE);
	intakeMotorLeft.set_brake_mode(MOTOR_BRAKE_BRAKE);

	// pros::Task deploy(IntakeController().deploy, NULL, "Robot Deploy");
	
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
		if(controller.get_digital(DIGITAL_B)){
			upperStack = -127;
			lowerStack = -127;
			intakeMotorLeft = -127;
			intakeMotorRight = -127;
		}
		if (controller.get_digital(DIGITAL_R1)){
			intakeMotorLeft = 127;
			intakeMotorRight = 127;
		}
		else if(controller.get_digital(DIGITAL_R2)){
			intakeMotorLeft = -127;
			intakeMotorRight = -127;
		}
		else if(!controller.get_digital(DIGITAL_B)){
			intakeMotorLeft = 0;
			intakeMotorRight = 0;
		}

		if (controller.get_digital(DIGITAL_L1)){
			upperStack = 127;
			lowerStack = 127;
		}
		else if(controller.get_digital(DIGITAL_L2)){
			upperStack = -127;
			lowerStack = -127;
		}
		else if(!controller.get_digital(DIGITAL_B)){
			upperStack = 0;
			lowerStack = 0;
		}

		//Control intakes
		// if (controller.get_digital(DIGITAL_B))
		// {
		// 	intakeMotorLeft = 0;
		// 	intakeMotorRight = 0;
		// }
		// else if (controller.get_digital(DIGITAL_A))
		// {
		// 	intakeMotorLeft = 127;
		// 	intakeMotorRight = 127;
		// }
		// else if (controller.get_digital(DIGITAL_Y))
		// {
		// 	intakeMotorLeft = -127;
		// 	intakeMotorRight = -127;
		// }

		//Controls shooting powerful
		// if (controller.get_digital(DIGITAL_X))
		// {
		// 	xPressed = true;
		// }
		// else if (xPressed)
		// {
		// 	shootPowerfulFunction();
		// 	xPressed = false;
		// }

		//Controls shooting two balls
		// if (controller.get_digital(DIGITAL_R2))
		// {
		// 	r2Pressed = true;
		// }
		// else if (r2Pressed) {
		// 	shootTwoBallsFunction();
		// 	r2Pressed = false;
		// }

		// //Controls shooting one ball
		// else if (controller.get_digital(DIGITAL_R1))
		// {
		// 	r1Pressed = true;
		// }
		// else if (r1Pressed) {
		// 	shootOneBallFunction();
		// 	r1Pressed = false;
		// }

		// //Controls ejecting two balls
		// if (controllerTwo.get_digital(DIGITAL_L2))
		// {
		// 	l2Pressed = true;
		// 	if (controllerTwo.get_digital(DIGITAL_LEFT)) {
		// 		shiftKeyPressed = true;
		// 	}
		// }
		// else if (l2Pressed) {
		// 	ejectTwoBallsFunction(!(shiftKeyPressed));
		// 	l2Pressed = false;
		// 	shiftKeyPressed = false;
		// }

		// //Controls ejecting one ball
		// else if (controllerTwo.get_digital(DIGITAL_L1))
		// {
		// 	l1Pressed = true;
		// 	if (controllerTwo.get_digital(DIGITAL_LEFT)) {
		// 		shiftKeyPressed = true;
		// 	}
		// }

		// else if (l1Pressed) {
		// 	ejectOneBallFunction(!(shiftKeyPressed));
		// 	l1Pressed = false;
		// 	shiftKeyPressed = false;
		// }

		//toggles top position 
		// if (controllerTwo.get_digital(DIGITAL_DOWN)){
		// 	IndexController().toggleTopPosition(true);
		// }
		// else if (controllerTwo.get_digital(DIGITAL_UP)){
		// 	IndexController().toggleTopPosition(false);
		// }

		// if (controller.get_digital(DIGITAL_RIGHT)) {
		// 	rightArrowPressed = true;
		// }
		// else if (rightArrowPressed) {
		// 	if (rightArrowActive) {
		// 		IndexController().toggleBottom(false);
		// 		IndexController().toggleTop(false);
		// 		rightArrowActive = false;
		// 	}
		// 	else {
		// 		IndexController().toggleBottom(true);
		// 		IndexController().toggleTop(true);
		// 		upperStack = -127;
		// 		lowerStack = -127;
		// 		topArrowActive = false;
		// 		rightArrowActive = true;
		// 	}
		// 	rightArrowPressed = false;
		// }
		// else if (controller.get_digital(DIGITAL_UP)) {
		// 	topArrowPressed = true;
		// }
		// else if (topArrowPressed) {
		// 	if (topArrowActive) {
		// 		IndexController().toggleBottom(false);
		// 		IndexController().toggleTop(false);
		// 		topArrowActive = false;
		// 	}
		// 	else {
		// 		IndexController().toggleBottom(true);
		// 		lowerStack = -127;
		// 		rightArrowActive = false;
		// 		topArrowActive = true;
		// 	}
		// 	topArrowPressed = false;
		// }

		pros::delay(10);
	}
}