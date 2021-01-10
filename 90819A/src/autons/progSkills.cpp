#include "autons/progSkills.h"

/**
 * Route to score first goal
*/
void firstGoal()
{
	// indexerFunctions.deploy(NULL);
	// pros::Task deploy(indexerFunctions.deploy, NULL, "Robot Deploy");
	// indexerFunctions.toggleIntakes(127);
	// pidForward(0, { {0, 0}, {0, 24} }, 100, 0.25, 100, 20, 20, 0, 0, 0, 0, 0, 0, true);
	// pidTurn(3 * M_PI / 2 - M_PI / 4, 100, 0.025, 120.0, 0.0, 0.0);
	// pidForward(3 * M_PI / 2 - M_PI / 4, { {0, 26}, {-18, 8} }, 80, 0.5, 100, 20, -20, 0, 0, 0, 0, 0, 0, true);
	// pros::Task intakeTaskController(IntakeController().stopIntakesAsync, NULL, "Intake Controller");
	// indexerFunctions.shootTwoBalls(NULL);
	// indexer.toggleTopPosition(true);
	// while (!IntakeController().getIntakeStatus())
	// {
	// 	pros::delay(10);
	// }
	IntakeController().toggleIntakes(127);
	PathFollowing()
		.withPath({ {0, 0, 0}, {15, 0, 0} }, 1)
		.ppMove();
	PathFollowing()
		.withPath({ {15, 0, 0}, {15, 15, 0}, {8, 40, -M_PI / 4} }, 1)
		.ppMove();

	pros::Task intakeTaskController(IntakeController().stopIntakesAsync, NULL, "Intake Controller");

	ShootController().shootTwoBalls(NULL);
	indexer.toggleTopPosition(true);
	while (!IntakeController().getIntakeStatus())
	{
		pros::delay(10);
	}
}

/**
 * Route to score second goal
*/
void secondGoal()
{
	PathFollowing()
		.withPath({ {9, 39.5, -M_PI / 4}, {25, 25, 0} }, 1)
		.ppMove();
	IntakeController().toggleIntakes(127);
	PathFollowing()
		.withPath({ {25, 25, 0}, {26, 39, 0} }, 1)
		.withSpeedCheck(5, 1, 250)
		.ppMove();
	IntakeController().toggleIntakes(0);
	PathFollowing()
		.withPath({ {26, 38, 0}, {38, 33, M_PI / 2} }, 1)
		.withSpeedCheck(2, 1, 250)
		.ppMove();
	IntakeController().toggleIntakes(127);
	pros::Task ejectController(EjectController()
		.setTopRoller(true)
		.ejectTwoBalls, NULL, "Eject Controller");
	PathFollowing()
		.withPath({ {38, 33, M_PI / 2}, {60.5, 33, M_PI / 2} }, 1)
		.withGains(25, 50)
		.ppMove();

	leftFrontMotor = 63;
	leftBackMotor = -63;
	rightFrontMotor = -63;
	rightBackMotor = 63;
	pros::delay(300);
	leftFrontMotor = 0;
	leftBackMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	PIDController()
		.withTargetTheta(0)
		.withLimit(100)
		.withMaxAngleError(0.025)
		.withTurnGains(120.0, 0.0, 0.0)
		.pidTurn();
	leftBackMotor = 63;
	leftFrontMotor = 63;
	rightFrontMotor = 63;
	rightBackMotor = 63;
	pros::delay(500);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	pros::Task intakeTaskController(IntakeController().stopIntakesAsync, NULL, "Intake Controller");
	ShootController().shootTwoBalls(NULL);
	indexer.toggleTopPosition(true);
	while (!IntakeController().getIntakeStatus())
	{
		pros::delay(10);
	}
}

/**
 * Route to score third goal
*/
void thirdGoal()
{
	leftBackMotor = -63;
	leftFrontMotor = -63;
	rightFrontMotor = -63;
	rightBackMotor = -63;
	pros::delay(300);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	PathFollowing()
		.withPath({ {60.5, 33, 0}, {80, 22, M_PI / 2} }, 1)
		.ppMove();
	IntakeController().toggleIntakes(127);
	PathFollowing()
		.withPath({ {80, 22, M_PI / 2}, {106, 22, M_PI / 2} }, 1)
		.ppMove();
	IntakeController().toggleIntakes(127);
	EjectController()
		.setTopRoller(true)
		.ejectOneBall(NULL);
	PathFollowing()
		.withPath({ {106, 20, M_PI / 2}, {100, 39, 0} }, 1)
		.withSpeedCheck(5, 0.5, 250)
		.ppMove();
	IntakeController().toggleIntakes(127);
	PathFollowing()
		.withPath({ {100, 37.5, 0}, {112, 32, M_PI / 4}, {119, 39, M_PI / 4} }, 1)
		.withSpeedCheck(2, 1, 250)
		.ppMove();

	pros::Task intakeTaskController(IntakeController().stopIntakesAsync, NULL, "Intake Controller 2");

	ShootController().shootTwoBalls(NULL);
	indexer.toggleTopPosition(true);
	while (!IntakeController().getIntakeStatus())
	{
		pros::delay(10);
	}
}

/**
 * Route to score fourth goal
*/
void fourthGoal()
{
	// pidBackward(5.76, {{-12, 115}, {11, 92}}, 100, 0.5, 50, 20, -50, 0, 0, 0, 0, 0, 0, true);
	// indexerFunctions.toggleIntakes(127);
	// pros::delay(250);
	// pidTurn(M_PI / 2 - 0.008, 100, 0.025, 120.0, 0.0, 0.0);
	PathFollowing()
		.withPath({ {118, 39, M_PI / 45}, {89, 6, M_PI} }, 1)
		.ppMove();
	IntakeController().toggleIntakes(127);
	pros::Task ejectController(EjectController()
		.setTopRoller(true)
		.ejectTwoBalls, NULL, "Eject Controller");
	PathFollowing()
		.withPath({ {89, 6, M_PI}, {89, -15, M_PI} }, 1)
		.withGains(25, 50)
		.ppMove();
	PathFollowing()
		.withPath({ {86, -15, M_PI}, {113.5, -15, M_PI / 2} }, 1)
		.ppMove();

	// indexerFunctions.poopOneBall(NULL);
	// pros::delay(500);
	// indexerFunctions.poopOneBall(NULL);
	// pidForward(M_PI / 2, {{12, 87}, {40, 87}}, 100, 0.5, 100, 20, 10, 0, 0, 0, 0, 0, 0, true);
	// pidTurn(0, 100, 0.025, 120.0, 0.0, 0.0);
	// pidForward(0, {{40, 84}, {40, 107}}, 100, 0.5, 100, 20, 10, 0, 0, 0, 0, 0, 0, true);
	// pros::Task intakeController2(IntakeController().stopIntakesAsync, NULL, "Intake Controller");
	// pros::delay(250);
	ShootController().shootOneBall(NULL);
	indexer.toggleTopPosition(true);
	// while (!IntakeController().getIntakeStatus())
	// {
	// 	pros::delay(10);
	// }
}

/**
 * Route to score fifth goal
*/
void fifthGoal()
{
	leftBackMotor = -63;
	leftFrontMotor = -63;
	rightFrontMotor = -63;
	rightBackMotor = -63;
	pros::delay(300);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	indexer.toggleTopPosition(true);
	IntakeController().toggleIntakes(127);
	pros::Task ejectController(EjectController()
		.setTopRoller(true)
		.ejectOneBall, NULL, "Eject Controller");
	PathFollowing()
		.withPath({ {112, -15, M_PI}, {112, -30, M_PI}, {114, -45, M_PI} }, 1)
		.withGains(25, 150)
		.ppMove();
	PathFollowing()
		.withPath({ {114, -45, M_PI}, {102, -45, M_PI}, {102, -69, M_PI} }, 1)
		.withSpeedCheck(5, 1, 250)
		.withGains(25, 300)
		.ppMove();
	PathFollowing()
		.withPath({ {102, -69, M_PI}, {111, -64, M_PI / 2 + M_PI / 4}, {118, -71, M_PI / 2 + M_PI / 4} }, 1)
		.withSpeedCheck(5, 1, 250)
		.ppMove();
	pros::Task intakeTaskController(IntakeController().stopIntakesAsync, NULL, "Intake Controller");
	ShootController().shootTwoBalls(NULL);
	indexer.toggleTopPosition(true);
	while (!IntakeController().getIntakeStatus())
	{
		pros::delay(10);
	}
}


/**
 * Route to score sixth goal
*/
void sixthGoal()
{
	pros::Task ejectController(EjectController()
		.setTopRoller(true)
		.ejectTwoBalls, NULL, "Eject Controller");
	PathFollowing()
		.withPath({ {117.8, -69.6, M_PI / 2 + M_PI / 4}, {87, -40, 3 * M_PI / 2} }, 1)
		.withSpeedCheck(2, 1, 250)
		.ppMove();
	IntakeController().toggleIntakes(127);
	PathFollowing()
		.withPath({ {87, -40, 3 * M_PI / 2}, {64, -37, 3 * M_PI / 2} }, 1)
		.withGains(25, 25)
		.ppMove();
	PathFollowing()
		.withPath({ {64, -37, M_PI}, {65, -65, M_PI} }, 1)
		.withSpeedCheck(5, 1, 250)
		.ppMove();
	pros::Task intakeTaskController(IntakeController().stopIntakesAsync, NULL, "Intake Controller");
	ShootController().shootTwoBalls(NULL);
	indexer.toggleTopPosition(true);
	while (!IntakeController().getIntakeStatus())
	{
		pros::delay(10);
	}
}

/**
 * Route to score seventh goal
*/
void seventhGoal()
{
	leftBackMotor = -63;
	leftFrontMotor = -63;
	rightFrontMotor = -63;
	rightBackMotor = -63;
	pros::delay(300);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	IntakeController().toggleIntakes(127);
	pros::Task ejectController(EjectController()
		.setTopRoller(true)
		.ejectOneBall, NULL, "Eject Controller");
	IntakeController().toggleIntakes(127);
	PathFollowing()
		.withPath({ {64, -62, M_PI}, {40, -51, 3 * M_PI / 2} }, 1)
		.ppMove();
	IntakeController().toggleIntakes(127);
	PathFollowing()
		.withPath({ {40, -52, 3 * M_PI / 2}, {24, -52, 3 * M_PI / 2} }, 1)
		.ppMove();
	PathFollowing()
		.withPath({ {24, -50, M_PI}, {28, -71, M_PI} }, 1)
		.withSpeedCheck(5, 0.5, 250)
		.ppMove();
	PathFollowing()
		.withPath({ {26, -71, M_PI}, {11, -66, M_PI + M_PI / 4}, {7, -72, M_PI + M_PI / 4} }, 1)
		.withSpeedCheck(5, 1, 250)
		.ppMove();
	pros::Task intakeTaskController(IntakeController().stopIntakesAsync, NULL, "Intake Controller");
	ShootController().shootTwoBalls(NULL);
	indexer.toggleTopPosition(true);
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
		.setTopRoller(true)
		.ejectTwoBalls, NULL, "Eject Controller");
	PathFollowing()
		.withPath({ {37, -36, 0}, {37, -14, 0} }, 1)
		.withGains(25, 50)
		.ppMove();
	PathFollowing()
		.withPath({ {37, -14, 3 * M_PI / 2}, {12, -16, 3 * M_PI / 2} }, 1)
		.withSpeedCheck(5, 1, 250)
		.ppMove();

	// pros::Task intakeTaskController(IntakeController().stopIntakesAsync, NULL, "Intake Controller");
	ShootController().shootOneBall(NULL);
	indexer.toggleTopPosition(true);
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
	//leftBackMotor = -63;
	//leftFrontMotor = -63;
	//rightFrontMotor = -63;
	//rightBackMotor = -63;
	//pros::delay(300);
	//leftBackMotor = 0;
	//leftFrontMotor = 0;
	//rightFrontMotor = 0;
	//rightBackMotor = 0;
	//pidTurn(2 * M_PI, 80, 0.025, 100.0, 0.0, 0.0);
	//// indexerFunctions.poopOneBall((void *) true);
	//pros::Task poopController(indexerFunctions.poopOneBall, (void *)true, "Poop Controller");
	//// indexer.toggleTop(true);
	//// indexer.toggleBottom(true);
	//// upperStack = 100;
	//// lowerStack = 127;
	//indexerFunctions.toggleIntakes(127);
	//pidForward(2 * M_PI, {{37, 20}, {37, 40}}, 63, 0.5, 50, 63, 20, 0, 0, 0, 0, 0, 0, true);
	//indexerFunctions.shootPowerful(NULL);
	//indexer.toggleTop(true);
	//indexer.toggleBottom(true);
	//upperStack = 127;
	//lowerStack = 127;
	//indexerFunctions.toggleIntakes(-127);
	//// pros::delay(2000);
	//// indexer.toggleTop(false);
	//// indexer.toggleBottom(false);
	//// upperStack = 127;
	//// lowerStack = 127;
	//// pros::delay(250);
	//// indexerFunctions.toggleIntakes(-127);
	//// pros::delay(250);
	//pros::delay(500);
	//leftBackMotor = -63;
	//leftFrontMotor = -63;
	//rightFrontMotor = -63;
	//rightBackMotor = -63;
	//pros::delay(750);
	//leftBackMotor = 0;
	//leftFrontMotor = 0;
	//rightFrontMotor = 0;
	//rightBackMotor = 0;
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

	firstGoal();
	secondGoal();
	thirdGoal();
	fourthGoal();
	fifthGoal();
	sixthGoal();
	seventhGoal();
	eighthGoal();
	leftFrontMotor.set_brake_mode(MOTOR_BRAKE_COAST);
	leftBackMotor.set_brake_mode(MOTOR_BRAKE_COAST);
	rightFrontMotor.set_brake_mode(MOTOR_BRAKE_COAST);
	rightBackMotor.set_brake_mode(MOTOR_BRAKE_COAST);

	// descoreMiddle();
	// seventhGoal();
	// eighthGoal();
	// ninthGoal();
}