#include "main.h"

using namespace std;

#define _USE_MATH_DEFINES

void initialize()
{
	pros::lcd::initialize();

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
	// should print about 2000 ms
	printf("IMU is done calibrating (took %d ms)\n", iter - time);
}

void disabled()
{
	position.resetGlobal();
}

void competition_initialize()
{
	displayInit(5);
}

void autonomous()
{
	position.resetGlobal();
	// leftFrontMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	// leftBackMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	// rightFrontMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	// rightBackMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);

	leftFrontMotor.set_brake_mode(MOTOR_BRAKE_COAST);
	leftBackMotor.set_brake_mode(MOTOR_BRAKE_COAST);
	rightFrontMotor.set_brake_mode(MOTOR_BRAKE_COAST);
	rightBackMotor.set_brake_mode(MOTOR_BRAKE_COAST);

	lowerStack.set_brake_mode(MOTOR_BRAKE_BRAKE);
	upperStack.set_brake_mode(MOTOR_BRAKE_BRAKE);
	intakeMotorLeft.set_brake_mode(MOTOR_BRAKE_BRAKE);
	intakeMotorRight.set_brake_mode(MOTOR_BRAKE_BRAKE);

	leftEncoder.reset();
	rightEncoder.reset();
	backEncoder.reset();

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
		runProgSkills();
		break;
	case 6:
		break;
	}
}

void opcontrol()
{
	driveControl();
}