#include "autons/progSkills.h"

/**
 * Route to score first goal
*/
void firstGoal()
{
	IntakeController().toggleIntakes(127);
	PathFollowing()
		.withPath({ {0, 0, 0}, {15, 0, 0} }, 1)
		.withGains(10, 50)
		.ppMove();
	PathFollowing()
		.withPath({ {15, 0, 0}, {15, 17, 0}, {27, 24, 0}, {27, 46.5, 0} }, 1)
		.ppMove();
	PathFollowing()
		.withPath({ {27, 47, 0}, {14, 37, -M_PI / 4}, {4, 42, -M_PI / 4} }, 1)
		.ppMove();

	upperStack = 127;
	lowerStack = 127;
	pros::delay(1250);
	upperStack = 0;
	lowerStack = 0;
	IntakeController().toggleIntakes(-127);
}

/**
 * Route to score second goal
*/
void secondGoal()
{
	PathFollowing()
		.withPath({ {6, 44.5, -M_PI / 4}, {38, 11, M_PI / 2} }, 1)
		.withGains(25, 150)
		.ppMove();
	IntakeController().toggleIntakes(127);
	PathFollowing()
		.withPath({ {38, 11, M_PI / 2}, {65, 11, M_PI / 2} }, 1)
		.withGains(10, 25)
		.ppMove();
	PIDController()
		.withTargetTheta(0)
		.withLimit(100)
		.withMaxAngleError(0.025)
		.withTurnGains(100.0, 0.0, 0.0)
		.pidTurn();
	PathFollowing()
		.withPath({ {65, 11, 0}, {65, 41, 0} }, 1)
		.withGains(15, 25)
		.withThresholdErrors(0.5, 0.17)
		.ppMove();
	upperStack = 127;
	lowerStack = 127;
	pros::delay(1250);
	upperStack = 0;
	lowerStack = 0;
}

/**
 * Route to score third goal
*/
void thirdGoal()
{

	PathFollowing()
		.withPath({ {65, 41, 0}, {63, 32, 0}, {90, 24, M_PI / 2} }, 1)
		.withGains(25, 150)
		.ppMove();

	PathFollowing()
		.withPath({ {90, 24, M_PI / 2}, {106, 24, M_PI / 2} }, 1)
		.ppMove();

	PathFollowing()
		.withPath({ {106, 24, 0}, {100, 30, 0}, {100, 48, 0} }, 1)
		.withGains(25, 150)
		.ppMove();

	PathFollowing()
		.withPath({ {100, 48, 0}, {110, 36, M_PI / 4}, {120, 45, M_PI / 4} }, 1)
		.withThresholdErrors(0.5, 0.17)
		.ppMove();
	upperStack = 127;
	lowerStack = 127;
	pros::delay(1250);
	upperStack = 0;
	lowerStack = 0;
}

/**
 * Route to score fourth goal
*/
void fourthGoal()
{
	PathFollowing()
		.withPath({ {120, 45, M_PI/4}, {87, 12, -M_PI} }, 1)
		.withGains(15, 150)
		.ppMove();

	PathFollowing()
		.withPath({ {87, 12, -M_PI}, {87, -13, -M_PI} }, 1)
		.withGains(10, 25)
		.ppMove();
	
	PIDController()
		.withTargetTheta(M_PI/2)
		.withLimit(100)
		.withMaxAngleError(0.025)
		.withTurnGains(100.0, 0.0, 0.0)
		.pidTurn();

	PathFollowing()
		.withPath({ {87, -13, M_PI/2}, {119, -13, M_PI/2} }, 1)
		.withThresholdErrors(0.5, 0.17)
		.ppMove();
	
	upperStack = 127;
	lowerStack = 127;
	pros::delay(1250);
	upperStack = 0;
	lowerStack = 0;
}

/**
 * Route to score fifth goal
*/
void fifthGoal()
{
	/*
	 * 114.4, -42.9
	 * 103.1, -72.5
	 * 123.1, -69
	 */
}

/**
 * Route to score sixth goal
*/
void sixthGoal()
{
	/*
	 * 70.2, -40
	 * 68.3, -57.2
	 * 68.5, -69.9
	 */
}

/**
 * Route to score seventh goal
*/
void seventhGoal()
{
	leftBackMotor = -80;
	leftFrontMotor = -80;
	rightFrontMotor = -80;
	rightBackMotor = -80;
	pros::delay(300);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	IntakeController().toggleIntakes(127);
	pros::Task ejectController(EjectController()
		.startEjecting,
		NULL, "Eject Controller");
	IntakeController().toggleIntakes(127);
	PathFollowing()
		.withPath({ {64, -62, M_PI}, {40, -52, 3 * M_PI / 2} }, 1)
		.ppMove();
	IntakeController().toggleIntakes(127);
	PathFollowing()
		.withPath({ {40, -52, 3 * M_PI / 2}, {24, -52, 3 * M_PI / 2} }, 1)
		.ppMove();
	PathFollowing()
		.withPath({ {24, -50, M_PI}, {28, -71.5, M_PI} }, 1)
		.withCoordinateReset(PositionController().getPosition()[0], -71)
		.withAngleReset(M_PI)
		.withSpeedCheck(5, 0.5, 250)
		.ppMove();
	PathFollowing()
		.withPath({ {28, -71.5, M_PI}, {11, -66, M_PI + M_PI / 4}, {7, -71, M_PI + M_PI / 4} }, 1)
		.withSpeedCheck(3.5, 1, 250)
		.ppMove();
	pros::Task intakeTaskController(IntakeController().stopIntakesAsync, NULL, "Intake Controller");
	ShootController().shoot(NULL);
	IndexController().toggleIndexing(false);
	while (!IntakeController().getIntakeStatus())
	{
		pros::delay(10);
	}
}

/**
 * Route to score eighth goal
*/
void eighthGoal()
{
	PathFollowing()
		.withPath({ {9, -70, M_PI + M_PI / 4}, {18, -61, M_PI + M_PI / 4}, {37, -36, 0} }, 1)
		.ppMove();
	IntakeController().toggleIntakes(127);
	pros::Task ejectController(EjectController()
		.startEjecting,
		NULL, "Eject Controller");
	PathFollowing()
		.withPath({ {37, -36, 0}, {37, -14, 0} }, 1)
		.withGains(25, 25)
		.ppMove();
	PathFollowing()
		.withPath({ {37, -14, 3 * M_PI / 2}, {9, -16, 3 * M_PI / 2} }, 1)
		.withSpeedCheck(5, 1, 250)
		.withCoordinateReset(10, PositionController().getPosition()[1])
		.ppMove();

	// pros::Task intakeTaskController(IntakeController().stopIntakesAsync, NULL, "Intake Controller");
	ShootController().shoot(NULL);
	pros::delay(250);
	IndexController().toggleIndexing(false);
	// while (!IntakeController().getIntakeStatus())
	// {
	// 	pros::delay(10);
	// }
}

/**
 * Route to score ninth goal
*/
void ninthGoal()
{
	PathFollowing()
		.withPath({ {12, -16, 3 * M_PI / 2}, {20, -16, M_PI + 4}, {32, 8, M_PI / 2} }, 1)
		.withGains(25, 150)
		.withSpeedCheck(0, 0, 5000)
		.withThresholdErrors(0.5, 0.016)
		.ppMove();
	PathFollowing()
		.withPath({ {32, 8, M_PI / 2}, {66, 8, M_PI / 2} }, 1)
		.withGains(25, 100)
		.withSpeedCheck(0, 0, 5000)
		.ppMove();
	pros::Task ejectController(EjectController()
		.startEjecting,
		NULL, "Eject Controller");

	PIDController()
		.withTargetTheta(M_PI)
		.withLimit(100)
		.withMaxAngleError(0.025)
		.withTurnGains(120.0, 0.0, 0.0)
		.pidTurn();

	IntakeController().toggleIntakes(127);

	// PathFollowing()
	// 	.withPath({{66, 0, M_PI}, {66, 12, M_PI}}, 1)
	// 	.withSpeedCheck(5, 0.5, 250)
	// 	.withGains(1000, 50)
	// 	.ppMove();
	IndexController().toggleIndexing(false);
	PathFollowing()
		.withPath({ {66, 6, M_PI}, {66, 0, M_PI} }, 1)
		.withSpeedCheck(5, 0.5, 250)
		.withGains(1000, 50)
		.ppMove();

	PathFollowing()
		.withPath({ {66, 0, M_PI}, {66, 6, M_PI} }, 1)
		.withGains(1000, 50)
		.ppMove();

	PathFollowing()
		.withPath({ {66, 6, M_PI}, {66, 0, M_PI} }, 1)
		.withSpeedCheck(5, 0.5, 250)
		.withGains(1000, 50)
		.ppMove();

	PathFollowing()
		.withPath({ {66, 0, M_PI}, {66, 6, M_PI} }, 1)
		.withGains(1000, 50)
		.ppMove();

	PathFollowing()
		.withPath({ {66, 6, M_PI}, {66, 0, M_PI} }, 1)
		.withSpeedCheck(5, 0.5, 250)
		.withGains(1000, 50)
		.ppMove();

	IntakeController().toggleIntakes(0);

	leftFrontMotor = 80;
	leftBackMotor = 80;
	pros::delay(500);
	ShootController().shoot(NULL);

	leftFrontMotor = -63;
	leftBackMotor = -63;
	rightFrontMotor = -63;
	rightBackMotor = -63;
	pros::delay(1000);
	leftFrontMotor = 0;
	leftBackMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	// PIDController()
	// 	.withTargetTheta(M_PI+M_PI/20)
	// 	.withLimit(100)
	// 	.withMaxAngleError(0.025)
	// 	.withTurnGains(120.0, 0.0, 0.0)
	// 	.pidTurn();
	// PathFollowing()
	// 	.withPath({{66, 0, M_PI}, {66, 8, M_PI}, {59, 5, M_PI}}, 1)
	// 	.withSpeedCheck(0, 0, 5000)
	// 	.ppMove();
}

/**
 * Runs full programming skills route
*/
void runProgSkills()
{
	// generatePath({{0, 0, 0}, {0, 10, 0}, {5, 15, M_PI/4}}, 1, 0.00, 0.00, 0.001, 5.0, 10.0, 3.0);

	// ppMove({{0, 0, 2*M_PI}, {0, 20, 2*M_PI}, {20, 40, M_PI/4}}, 1, 0.00, 0.00, 0.001, 5.0, 10.0, 3.0, 6, 0.25, 30, 100);

	// ppMove({{0, 0, 0}, {0, -40, M_PI/2+M_PI/4}}, 1, 0.00, 0.00, 0.001, 5.0, 10.0, 3.0, 6, 0.25, 30, 300, 0.008);

	// moveRobot({4	, 1, 0.01}, 100, 100, 200);
	// 	moveRobot({1, 4, 50}, 100, 100, 100);
	// moveRobot({-4, 1, 50}, 100, 100, 100);
	// moveRobot({-1, 4, 50}, 100, 100, 100);
	// moveRobot({1, -4, 50}, 100, 100, 100);
	// moveRobot({4, -1, 50}, 100, 100, 100);
	// moveRobot({-1, -4, 50}, 100, 100, 100);
	// moveRobot({-4, -1, 50}, 100, 100, 100);
	PositionController().resetGlobal();

	pros::Task deploy(IntakeController().deploy, NULL, "Robot Deploy");
	firstGoal();
	secondGoal();
	thirdGoal();
	fourthGoal();
	// fifthGoal();
	// sixthGoal();
	// seventhGoal();
	// eighthGoal();
	// ninthGoal();
	leftFrontMotor.set_brake_mode(MOTOR_BRAKE_COAST);
	leftBackMotor.set_brake_mode(MOTOR_BRAKE_COAST);
	rightFrontMotor.set_brake_mode(MOTOR_BRAKE_COAST);
	rightBackMotor.set_brake_mode(MOTOR_BRAKE_COAST);

	// descoreMiddle();
	// seventhGoal();
	// eighthGoal();
	// ninthGoal();
}