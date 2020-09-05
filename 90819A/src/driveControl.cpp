#include "driveControl.h"

bool digitalR1Pressed = false;
bool digitalR2Pressed = false;

void moveDrive(int motorSpeed, int turnSpeed, int strafeSpeed)
{
	//forward: all positive
	//right: lF and rB positive, lB and rF negative
	//back: all negative
	//left: lB and rF positive, lF and rB negative

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

void shootOneBallFunction() {
	pros::Task indexShootingController(indexerFunctions.shootOneBall, NULL, "Ball Shooter");
}

void shootTwoBallsFunction() {
	pros::Task indexShootingController(indexerFunctions.shootTwoBalls, NULL, "Ball Shooter 2");
}

void driveControl()
{

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
		printf("%d\n", lineSensorTop.get_value());
		//calcPosition();
		//resetGlobal();
		//printf("Left: %.3f\n", leftEncoder.get_value()* M_PI / 180.0 * WHEEL_DIAMETER /2);
		//printf("Right: %.3f\n", rightEncoder.get_value()* M_PI / 180.0 * WHEEL_DIAMETER /2);
		//printf("Back: %.3f\n", backEncoder.get_value()* M_PI / 180.0 * WHEEL_DIAMETER /2);

		int motorSpeed = controller.get_analog(ANALOG_LEFT_Y);
		int strafeSpeed = controller.get_analog(ANALOG_LEFT_X);
		int turnSpeed = controller.get_analog(ANALOG_RIGHT_X);

		if (turnSpeed > 100)
			turnSpeed = 127;
		else if (turnSpeed < -100)
			turnSpeed = -127;

		moveDrive(motorSpeed, turnSpeed, strafeSpeed);

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

		// if (controller.get_digital(DIGITAL_L1))
		// {
		// 	upperStack = 127;
		// }

		// else if (controller.get_digital(DIGITAL_L2))
		// {
		// 	upperStack = 0;
		// }

		if (controller.get_digital(DIGITAL_R1))
		{
			digitalR1Pressed = true;
		}
		else if(digitalR1Pressed) {
			shootOneBallFunction();
			digitalR1Pressed = false;
		}

		if (controller.get_digital(DIGITAL_R2))
		{
			digitalR2Pressed = true;
		}
		else if (digitalR2Pressed) {
			shootTwoBallsFunction();
			digitalR2Pressed = false;
		}

		if (controller.get_digital(DIGITAL_LEFT))
		{
			upperStack = -127;
			lowerStack = 127;
		}

		//pros::Task indexShootingController(indexerFunctions.shootBall, NULL, "Ball Shooter");

		pros::delay(10);
	}
}