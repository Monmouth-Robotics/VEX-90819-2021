#include "main.h"

using namespace std;

#define _USE_MATH_DEFINES

void initialize()
{
	pros::lcd::initialize();
}

void disabled() {
	position.resetGlobal();
}


void competition_initialize()
{
	displayInit(5);
}

void autonomous()
{
	position.resetGlobal();
	leftFrontMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	leftBackMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	rightFrontMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	rightBackMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);

	leftEncoder.reset();
	rightEncoder.reset();
	backEncoder.reset();

	switch (getAutonCode()) {
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		runProgSkills();
		break;
	case 6:
		break;
	}
}

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

	while (true)
	{
		//calcPosition();
		printf("Theta: %.3f\n", position.getTheta() * 180 / M_PI);
		printf("X: %.3f\n", position.getPosition()[0]);
		printf("Y: %.3f\n\n", position.getPosition()[1]);
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

		if (controller.get_digital(DIGITAL_L1))
		{
			upperStack = 127;
		}

		else if (controller.get_digital(DIGITAL_L2))
		{
			upperStack = 0;
		}

		if (controller.get_digital(DIGITAL_R1))
		{
			lowerStack = 80;
		}

		else if (controller.get_digital(DIGITAL_R2))
		{
			lowerStack = 0;
		}

		if (controller.get_digital(DIGITAL_LEFT))
		{
			upperStack = -127;
		}

		pros::delay(10);
	}
}