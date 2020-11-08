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

void shootOneBallFunction()
{
	pros::Task indexShootingController(indexerFunctions.shootOneBall, NULL, "Ball Shooter");
}

void shootTwoBallsFunction()
{
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

	//imuLeft.reset();
	//imuRight.reset();

	//position.resetGlobal();

	//int time = pros::millis();
	//int iter = 0;
	//while (imuLeft.is_calibrating() || imuRight.is_calibrating())
	//{
	//	printf("IMU calibrating... %d\n", iter);
	//	iter += 10;
	//	pros::delay(10);
	//}
	//printf("IMU is done calibrating (took %d ms)\n", iter - time);

	while (true)
	{
		// printf("%d\n", lineSensorTop.get_value());
		// calcPosition();
		// printf("Ultrasonic Top: %d\n", ultrasonicTop.get_value());
		// printf("Ultrasonic Bottom: %d\n", ultrasonicBottom.get_value());

		// printf("Left IMU: %f\n", imuLeft.get_heading());
		// printf("Right IMU: %f\n", imuRight.get_heading());


		opticalSensor.set_led_pwm(100);
		// printf("Optical: %lf\n", opticalSensor.get_hue());

		// printf("Left: %d\n", leftEncoder.get_value());
		// printf("Right: %d\n", rightEncoder.get_value());
		// printf("Back: %d\n", backEncoder.get_value());

		// printf(positionController.getPosition());
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
		// 	upperStack = -127;
		// 	lowerStack = 127;
		// }

		if (controller.get_digital(DIGITAL_R1))
		{
			// upperStack = 127;
			// lowerStack = 127;

			shootOneBallFunction();
		}

		if (controller.get_digital(DIGITAL_R2))
		{
			upperStack = 0;
			lowerStack = 0;
		}

		if (controller.get_digital(DIGITAL_L1))
		{
			upperStack = -127;
			lowerStack = 127;
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