#include "autons/progSkills.h"

bool intakeStatus = false;

/**
 * Stops intakes when two blue balls need to be descored
*/
void stopIntakesAsync(void *ignore)
{
	intakeStatus = false;

	//Waits for intakes to contain red ball
	while (indexer.getIntakeColor() != "red")
	{
		pros::delay(10);
	}

	intakeStatus = true;

	//Outtakes until intakes no longer contain red ball
	while (indexer.getIntakeColor() == "red")
	{
		indexerFunctions.toggleIntakes(-127);
	}

	indexerFunctions.toggleIntakes(0);
}

/**
 * Stops intakes when one blue ball needs to be descored
*/
void stopIntakesAsyncOne(void *ignore)
{
	intakeStatus = false;

	//Waits for intakes to contain one blue ball
	while (indexer.getIntakeColor() != "blue")
	{
		pros::delay(10);
	}
	indexerFunctions.toggleIntakes(0);
	intakeStatus = true;
}

/**
 * Route to score first goal
*/
void firstGoal()
{
	indexerFunctions.toggleIntakes(127);
	pidForward(0, {{0, 0}, {0, 24}}, 127, 0.25, 100, 20, 20, 0, 0, 0, 0, 0, 0, true);
	pidTurn(3 * M_PI / 2 - M_PI / 4, 80, 0.025, 120.0, 0.0, 0.0);
	pidForward(3 * M_PI / 2 - M_PI / 4, {{0, 24}, {-18, 8}}, 80, 0.5, 100, 20, -20, 0, 0, 0, 0, 0, 0, true);
	pros::Task intakeController(stopIntakesAsync, NULL, "Intake Controller");
	indexerFunctions.shootOneBall();
	indexerFunctions.shootOneBall();
	indexer.toggleTopPosition(true);
	while (!intakeStatus)
	{
		pros::delay(10);
	}
}

/**
 * Route to score second goal
*/
void secondGoal()
{
	pidBackward(3.92, {{-20, 0}, {0, 24}}, 80, 0.5, 50, 63, -20, 0, 0, 0, 0, 0, 0, true);
	indexerFunctions.toggleIntakes(127);
	pidTurn(M_PI * 3 / 2, 80, 0.025, 140.0, 0.0, 0.0);
	pidForward(M_PI * 3 / 2, {{0, 27}, {-14, 27}}, 80, 0.5, 50, 50, -30, 0, 0, 0, 0, 0, 0, true);
	pidTurn(0, 80, 0.025, 100.0, 0.0, 0.0);
	// indexerFunctions.poopOneBall(NULL);
	// pros::delay(500);
	// indexerFunctions.poopOneBall(NULL);
	pros::Task poopController(indexerFunctions.poopTwoBalls, (void *)true, "Poop Controller");
	// pros::Task intakeController(stopIntakesAsync, NULL, "Intake Controller");
	pidForward(0, {{-5, 24}, {-5, 59}}, 80, 0.5, 30, 50, 50, 0, 0, 0, 0, 0, 0, true);
	pidTurn(M_PI * 3 / 2, 80, 0.025, 100.0, 0.0, 0.0);
	leftBackMotor = 63;
	leftFrontMotor = 63;
	rightFrontMotor = 63;
	rightBackMotor = 63;
	pros::delay(500);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	pros::Task intakeController2(stopIntakesAsync, NULL, "Intake Controller2");
	indexerFunctions.shootOneBall();
	indexerFunctions.shootOneBall();
	indexer.toggleTopPosition(true);
	while (!intakeStatus)
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
	pros::delay(750);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	indexerFunctions.toggleIntakes(127);
	indexer.toggleTopPosition(true);
	pidTurn(2 * M_PI, 80, 0.025, 100.0, 0.0, 0.0);
	pros::Task poopController(indexerFunctions.poopOneBall, (void *)true, "Poop Controller");
	pidForward(0, {{0, 60}, {0, 104}}, 80, 0.5, 30, 50, 50, 0, 0, 0, 0, 0, 0, true);
	// leftBackMotor = -63;
	// leftFrontMotor = -63;
	// rightFrontMotor = -63;
	// rightBackMotor = -63;
	// pros::delay(500);
	// leftBackMotor = 0;
	// leftFrontMotor = 0;
	// rightFrontMotor = 0;
	// rightBackMotor = 0;
	pidTurn(5.529, 127, 0.025, 100.0, 0.0, 0.0);
	pidForward(5.529, {{-12, 115}, {-13, 116}}, 80, 0.5, 50, 20, -20, 0, 0, 0, 0, 0, 0, true);
	// pros::delay(250);
	pros::Task intakeController2(stopIntakesAsync, NULL, "Intake Controller 2");
	pros::delay(250);
	indexerFunctions.shootOneBall();
	indexer.toggleTopPosition(true);
	while (!intakeStatus)
	{
		pros::delay(10);
	}
}

/**
 * Route to score fourth goal
*/
void fourthGoal()
{
	pidBackward(5.76, {{-12, 115}, {12, 89}}, 80, 0.5, 50, 20, -50, 0, 0, 0, 0, 0, 0, true);
	indexerFunctions.toggleIntakes(127);
	pidTurn(M_PI / 2, 127, 0.025, 100.0, 0.0, 0.0);
	pros::Task poopController(indexerFunctions.poopTwoBalls, (void *)true, "Poop Controller");
	// indexerFunctions.poopOneBall(NULL);
	// pros::delay(500);
	// indexerFunctions.poopOneBall(NULL);
	pidForward(M_PI / 2, {{12, 87}, {40, 87}}, 80, 0.5, 100, 20, 10, 0, 0, 0, 0, 0, 0, true);

	pidTurn(0, 80, 0.025, 100.0, 0.0, 0.0);
	pidForward(0, {{40, 84}, {40, 111}}, 80, 0.5, 100, 20, 10, 0, 0, 0, 0, 0, 0, true);
	pros::Task intakeController2(stopIntakesAsyncOne, NULL, "Intake Controller");
	indexerFunctions.shootOneBall();
	indexer.toggleTopPosition(true);
	while (!intakeStatus)
	{
		pros::delay(10);
	}
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
	pros::delay(500);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	pidTurn(M_PI / 2, 80, 0.025, 120.0, 0.0, 0.0);
	indexerFunctions.toggleIntakes(127);
	pros::Task poopController(indexerFunctions.poopOneBall, NULL, "Poop Controller");
	pidForward(M_PI / 2, {{41, 111}, {66, 111}}, 80, 0.5, 100, 20, 35, 0, 0, 0, 0, 0, 0, true);

	leftBackMotor = -63;
	leftFrontMotor = 63;
	rightFrontMotor = -63;
	rightBackMotor = 63;
	pros::delay(750);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	pidForward(M_PI / 2, {{80, 97}, {92, 97}}, 80, 0.5, 100, 20, 20, 0, 0, 0, 0, 0, 0, true);
	pros::delay(250);
	pidBackward(M_PI / 2, {{94, 95}, {73, 95}}, 80, 0.5, 100, 20, 20, 0, 0, 0, 0, 0, 0, true);
	pidTurn(M_PI / 4, 80, 0.025, 140.0, 0.0, 0.0);
	pidForward(M_PI / 4, {{91, 113}, {92, 114}}, 80, 0.5, 100, 15, 20, 0, 0, 0, 0, 0, 0, true);
	pros::Task intakeController2(stopIntakesAsync, NULL, "Intake Controller");
	indexerFunctions.shootOneBall();
	indexerFunctions.shootOneBall();
	indexer.toggleTopPosition(true);
	while (!intakeStatus)
	{
		pros::delay(10);
	}
}

/**
 * Route to descore middle goal
*/
void descoreMiddle()
{
	indexerFunctions.toggleIntakes(127);
	pidBackward(M_PI / 2, {{92, 108}, {62, 108}}, 80, 0.5, 100, 20, 20, 0, 0, 0, 0, 0, 0, true);
	pidTurn(M_PI, 80, 0.025, 100.0, 0.0, 0.0);
	pros::Task poopController(indexerFunctions.poopTwoBalls, (void *)true, "Poop Controller");

	indexerFunctions.toggleIntakes(127);
	pidForward(M_PI, {{62, 105}, {62, 57}}, 80, 0.5, 100, 15, -30, 0, 0, 0, 0, 0, 0, true);
	pidTurn(3 * M_PI / 2, 80, 0.025, 140.0, 0.0, 0.0);
	leftBackMotor = 80;
	leftFrontMotor = 80;
	rightFrontMotor = 80;
	rightBackMotor = 80;
	pros::delay(600);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	leftBackMotor = -63;
	leftFrontMotor = -63;
	rightFrontMotor = -63;
	rightBackMotor = -63;
	pros::delay(500);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
}

/**
 * Route to score sixth goal
*/
void sixthGoal()
{
	pidTurn(M_PI / 2, 80, 0.025, 100.0, 0.0, 0.0);
	//might need to be negative
	pidLeft(M_PI / 2, {{60, 50}, {60, 64}}, 80, 0.5, 50, 10, 20, 0, 0, 0, 0, 0, 0, true);
	pidForward(M_PI / 2, {{60, 64}, {87, 64}}, 80, 0.5, 100, 15, 30, 0, 0, 0, 0, 0, 0, true);
	// pros::Task intakeController2(stopIntakesAsyncOne, NULL, "Intake Controller");
	pros::Task intakeController(stopIntakesAsync, NULL, "Intake Controller");
	indexerFunctions.shootOneBall();
	// indexer.toggleTopPosition(true);

	while (!intakeStatus)
	{
		pros::delay(10);
	}
}

/**
 * Route to score seventh goal
*/
void seventhGoal()
{
	pidBackward(M_PI / 2, {{83, 61}, {73, 61}}, 80, 0.5, 50, 20, 20, 0, 0, 0, 0, 0, 0, true);
	indexerFunctions.toggleIntakes(127);
	pidTurn(M_PI, 80, 0.025, 100.0, 0.0, 0.0);
	pros::Task poopController(indexerFunctions.poopOneBall, (void *)false, "Poop Controller");
	// indexerFunctions.poopOneBall(NULL);
	// indexerFunctions.poopOneBall(NULL);
	// indexer.toggleTopPosition(false);

	pidForward(M_PI, {{77, 61}, {77, 18}}, 80, 0.5, 50, 15, -30, 0, 0, 0, 0, 0, 0, true);

	pidBackward(M_PI, {{76, 18}, {76, 27}}, 80, 0.5, 50, 10, -20, 0, 0, 0, 0, 0, 0, true);
	pidTurn(M_PI / 2 + M_PI / 4, 80, 0.025, 100.0, 0.0, 0.0);
	pidForward(M_PI / 2 + M_PI / 4, {{94, 12}, {95, 11}}, 80, 0.5, 50, 20, 30, 0, 0, 0, 0, 0, 0, true);
	pros::Task intakeController(stopIntakesAsync, NULL, "Intake Controller");
	indexerFunctions.shootOneBall();
	while (!intakeStatus)
	{
		pros::delay(10);
	}
}

/**
 * Route to score eighth goal
*/
void eighthGoal()
{
	pidBackward(M_PI / 2 + M_PI / 4, {{95, 12}, {88, 18}}, 80, 0.5, 50, 10, 20, 0, 0, 0, 0, 0, 0, true);
	indexerFunctions.toggleIntakes(127);
	pidTurn(M_PI, 80, 0.025, 100.0, 0.0, 0.0);
	indexerFunctions.poopTwoBalls((void *)false);
	pidRight(M_PI, {{88, 18}, {40, 18}}, 80, 0.5, 50, 10, 20, 0, 0, 0, 0, 0, 0, true);
	leftBackMotor = 63;
	leftFrontMotor = 63;
	rightFrontMotor = 63;
	rightBackMotor = 63;
	pros::delay(500);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	pros::Task intakeController(stopIntakesAsyncOne, NULL, "Intake Controller");
	indexerFunctions.shootOneBall();
	indexer.toggleTopPosition(true);
	while (!intakeStatus)
	{
		pros::delay(10);
	}
}

/**
 * Route to score ninth goal
*/
void ninthGoal()
{
	leftBackMotor = -63;
	leftFrontMotor = -63;
	rightFrontMotor = -63;
	rightBackMotor = -63;
	pros::delay(250);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	indexerFunctions.toggleIntakes(127);
	pidTurn(2 * M_PI, 80, 0.025, 100.0, 0.0, 0.0);
	pros::Task poopController(indexerFunctions.poopOneBall, (void *)true, "Poop Controller");
	pidForward(2 * M_PI, {{36, 20}, {36, 43}}, 80, 1, 50, 20, 30, 0, 0, 0, 0, 0, 0, true);
	indexerFunctions.shootOneBall();

	pros::delay(250);
	indexerFunctions.toggleIntakes(-127);
	leftBackMotor = -63;
	leftFrontMotor = -63;
	rightFrontMotor = -63;
	rightBackMotor = -63;
	pros::delay(750);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
}

/**
 * Runs full programming skills route
*/
void runProgSkills()
{
	firstGoal();
	secondGoal();
	thirdGoal();
	fourthGoal();
	fifthGoal();
	descoreMiddle();
	sixthGoal();
	seventhGoal();
	eighthGoal();
	ninthGoal();
}
