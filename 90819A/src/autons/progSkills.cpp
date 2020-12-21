#include "autons/progSkills.h"

bool intakeStatus = false;

/**
 * Stops intakes when two blue balls need to be descored
*/
void stopIntakesAsync(void *ignore)
{
	intakeStatus = false;

	while (indexer.getIntakeColor() != "blue")
	{
		pros::delay(10);
	}

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

	// indexerFunctions.toggleIntakes(0);

	// pros::delay(500);

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
	// indexerFunctions.deploy(NULL);
	// pros::Task deploy(indexerFunctions.deploy, NULL, "Robot Deploy");
	// indexerFunctions.toggleIntakes(127);
	// pidForward(0, { {0, 0}, {0, 24} }, 100, 0.25, 100, 20, 20, 0, 0, 0, 0, 0, 0, true);
	// pidTurn(3 * M_PI / 2 - M_PI / 4, 100, 0.025, 120.0, 0.0, 0.0);
	// pidForward(3 * M_PI / 2 - M_PI / 4, { {0, 26}, {-18, 8} }, 80, 0.5, 100, 20, -20, 0, 0, 0, 0, 0, 0, true);
	// pros::Task intakeController(stopIntakesAsync, NULL, "Intake Controller");
	// indexerFunctions.shootTwoBalls(NULL);
	// indexer.toggleTopPosition(true);
	// while (!intakeStatus)
	// {
	// 	pros::delay(10);
	// }

	indexerFunctions.toggleIntakes(127);
	//ppMove({{0, 0, 0}, {15, 0, 0}}, 1, 0.00, 0.00, 0.001, 5.0, 10.0, 3.0, 10, 0.25, 25, 300, 0.08);
	//ppMove({{15, 0, 0}, {15, 15, 0}, {9, 39.5, -M_PI / 4}}, 1, 0.00, 0.00, 0.001, 5.0, 10.0, 3.0, 10, 0.5, 25, 300, 0.08);
	pros::Task intakeController2(stopIntakesAsync, NULL, "Intake Controller2");

	indexerFunctions.shootTwoBalls(NULL);
	indexer.toggleTopPosition(true);
	while (!intakeStatus)
	{
		pros::delay(10);
	}
	// leftFrontMotor = -127;
	// leftBackMotor = -127;
	// rightFrontMotor = -127;
	// rightBackMotor = -127;

	// pros::delay(1000);

	// leftFrontMotor = 0;
	// leftBackMotor = 0;
	// rightFrontMotor = 0;
	// rightBackMotor = 0;
}

/**
 * Route to score second goal
*/
void secondGoal()
{
	//ppMove({{9, 39.5, -M_PI / 4}, {25, 25, 0}}, 1, 0.00, 0.00, 0.001, 5.0, 10.0, 3.0, 10, 0.5, 25, 300, 0.08);
	indexerFunctions.toggleIntakes(127);
	//ppMove({{25, 25, 0}, {26, 38, 0}}, 1, 0.00, 0.00, 0.001, 5.0, 10.0, 3.0, 10, 0.5, 25, 300, 0.08);
	indexerFunctions.toggleIntakes(0);
	//ppMove({{26, 39, 0}, {38, 33, M_PI / 2}}, 1, 0.00, 0.00, 0.001, 5.0, 10.0, 3.0, 10, 0.5, 25, 300, 0.08);
	indexerFunctions.toggleIntakes(127);
	pros::Task poopController(indexerFunctions.poopTwoBalls, (void *)true, "Poop Controller");
	//ppMove({{38, 33, M_PI / 2}, {60.5, 33, M_PI / 2}}, 1, 0.00, 0.00, 0.001, 5.0, 10.0, 3.0, 10, 0.5, 25, 100, 0.08);

	// pidBackward(3.92, { {-20, 0}, {0, 24} }, 100, 0.5, 50, 80, -20, 0, 0, 0, 0, 0, 0, true);
	// indexerFunctions.toggleIntakes(127);
	// pidTurn(M_PI * 3 / 2, 100, 0.025, 140.0, 0.0, 0.0);
	// pidForward(M_PI * 3 / 2, { {0, 27}, {-14, 27} }, 80, 0.5, 50, 50, -30, 0, 0, 0, 0, 0, 0, true);
	// pidTurn(0, 100, 0.025, 140.0, 0.0, 0.0);
	// indexerFunctions.poopOneBall(NULL);
	// pros::delay(500);
	// indexerFunctions.poopOneBall(NULL);
	// pros::Task poopController(indexerFunctions.poopTwoBalls, (void*)true, "Poop Controller");
	// pros::Task intakeController(stopIntakesAsync, NULL, "Intake Controller");
	// pidForward(0, { {-12, 24}, {-12, 59} }, 100, 0.5, 30, 50, 50, 0, 0, 0, 0, 0, 0, true);
	leftFrontMotor = 63;
	leftBackMotor = -63;
	rightFrontMotor = -63;
	rightBackMotor = 63;
	pros::delay(300);
	leftFrontMotor = 0;
	leftBackMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	pidTurn(0, 100, 0.025, 120.0, 0.0, 0.0);
	leftBackMotor = 63;
	leftFrontMotor = 63;
	rightFrontMotor = 63;
	rightBackMotor = 63;
	pros::delay(500);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	pros::Task intakeController2(stopIntakesAsync, NULL, "Intake Controller");
	indexerFunctions.shootTwoBalls(NULL);
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
	pros::delay(300);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	//ppMove({{60.5, 33, 0}, {80, 22, M_PI / 2}}, 1, 0.00, 0.00, 0.001, 5.0, 10.0, 3.0, 10, 0.5, 25, 300, 0.08);
	indexerFunctions.toggleIntakes(127);
	//ppMove({{80, 22, M_PI / 2}, {106, 22, M_PI / 2}}, 1, 0.00, 0.00, 0.001, 5.0, 10.0, 3.0, 10, 0.5, 25, 100, 0.08);

	// pros::Task poopController(indexerFunctions.poopOneBall, (void *)true, "Poop Controller");

	indexerFunctions.toggleIntakes(127);

	indexerFunctions.poopOneBall((void *)true);

	//ppMove({{106, 20, M_PI / 2}, {100, 37.5, 0}}, 1, 0.00, 0.00, 0.001, 5.0, 10.0, 3.0, 10, 0.5, 25, 300, 0.08);
	indexerFunctions.toggleIntakes(127);
	//ppMove({{100, 38, 0}, {112, 32, M_PI / 4}, {118, 38, M_PI / 4}}, 1, 0.00, 0.00, 0.001, 5.0, 10.0, 3.0, 10, 1.0, 25, 300, 0.08);

	// leftBackMotor = -63;
	// leftFrontMotor = -63;
	// rightFrontMotor = -63;
	// rightBackMotor = -63;
	// pros::delay(600);
	// leftBackMotor = 0;
	// leftFrontMotor = 0;
	// rightFrontMotor = 0;
	// rightBackMotor = 0;
	// indexerFunctions.toggleIntakes(127);
	// indexer.toggleTopPosition(true);
	// pidTurn(2 * M_PI, 100, 0.025, 120.0, 0.0, 0.0);
	// pros::Task poopController(indexerFunctions.poopOneBall, (void *)true, "Poop Controller");
	// pidForward(0, {{-1, 60}, {-1, 104}}, 80, 0.5, 30, 50, 50, 0, 0, 0, 0, 0, 0, true);
	// // leftBackMotor = -63;
	// // leftFrontMotor = -63;
	// // rightFrontMotor = -63;
	// // rightBackMotor = -63;
	// // pros::delay(500);
	// // leftBackMotor = 0;
	// // leftFrontMotor = 0;
	// // rightFrontMotor = 0;
	// // rightBackMotor = 0;
	// pidTurn(5.529, 127, 0.025, 120.0, 0.0, 0.0);
	// pidForward(5.529, {{-13, 115}, {-14, 116}}, 100, 0.5, 50, 20, -30, 0, 0, 0, 0, 0, 0, true);
	// pros::delay(250);
	// pros::delay(250);
	pros::Task intakeController2(stopIntakesAsync, NULL, "Intake Controller 2");
	// pros::delay(250);
	// pros::delay(150);
	indexerFunctions.shootTwoBalls(NULL);
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
	// pidBackward(5.76, {{-12, 115}, {11, 92}}, 100, 0.5, 50, 20, -50, 0, 0, 0, 0, 0, 0, true);
	// indexerFunctions.toggleIntakes(127);
	// pros::delay(250);
	// pidTurn(M_PI / 2 - 0.008, 100, 0.025, 120.0, 0.0, 0.0);
	//ppMove({{118, 39, M_PI / 45}, {89, 8, M_PI}}, 1, 0.00, 0.00, 0.001, 5.0, 10.0, 3.0, 10, 1.0, 25, 300, 0.08);
	indexerFunctions.toggleIntakes(127);
	pros::Task poopController(indexerFunctions.poopTwoBalls, (void *)true, "Poop Controller");
	//ppMove({{89, 9, M_PI}, {89, -15, M_PI}}, 1, 0.00, 0.00, 0.001, 5.0, 10.0, 3.0, 10, 1.0, 25, 100, 0.08);
	//ppMove({{86, -15, M_PI}, {113, -15, M_PI / 2}}, 1, 0.00, 0.00, 0.001, 5.0, 10.0, 3.0, 10, 1.0, 25, 300, 0.08);

	// indexerFunctions.poopOneBall(NULL);
	// pros::delay(500);
	// indexerFunctions.poopOneBall(NULL);
	// pidForward(M_PI / 2, {{12, 87}, {40, 87}}, 100, 0.5, 100, 20, 10, 0, 0, 0, 0, 0, 0, true);
	// pidTurn(0, 100, 0.025, 120.0, 0.0, 0.0);
	// pidForward(0, {{40, 84}, {40, 107}}, 100, 0.5, 100, 20, 10, 0, 0, 0, 0, 0, 0, true);
	// pros::Task intakeController2(stopIntakesAsync, NULL, "Intake Controller");
	// pros::delay(250);
	indexerFunctions.shootOneBall(NULL);
	indexer.toggleTopPosition(true);
	// while (!intakeStatus)
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
	indexerFunctions.toggleIntakes(127);
	pros::Task poopController(indexerFunctions.poopOneBall, (void *)true, "Poop Controller");
	//ppMove({{112, -15, M_PI / 2}, {112, -30, M_PI}, {112, -40, M_PI}}, 1, 0.00, 0.00, 0.001, 5.0, 10.0, 3.0, 10, 1.0, 28, 300, 0.08);
	//ppMove({{101, -40, M_PI}, {101, -68, M_PI}}, 1, 0.00, 0.00, 0.001, 5.0, 10.0, 3.0, 10, 1.0, 28, 300, 0.08);
	//ppMove({{101, -68, M_PI}, {113, -62, M_PI / 2 + M_PI / 4}, {119, -69, M_PI / 2 + M_PI / 4}}, 1, 0.00, 0.00, 0.001, 5.0, 10.0, 3.0, 10, 1.0, 28, 300, 0.08);

	// pidRight(M_PI / 2, {{75, 112}, {75, 98}}, 100, 0.5, 100, 20, 20, 0, 0, 0, 0, 0, 0, true);

	// leftBackMotor = -63;
	// leftFrontMotor = 63;
	// rightFrontMotor = -63;
	// rightBackMotor = 63;
	// pros::delay(500);
	// leftBackMotor = 0;
	// leftFrontMotor = 0;
	// rightFrontMotor = 0;
	// rightBackMotor = 0;
	// pidForward(M_PI / 2, {{80, 98}, {89, 98}}, 100, 0.5, 100, 20, 20, 0, 0, 0, 0, 0, 0, true);
	// pros::delay(250);
	// pidBackward(M_PI / 2, {{94, 95}, {79, 95}}, 100, 0.5, 100, 20, 20, 0, 0, 0, 0, 0, 0, true);
	// pidTurn(M_PI / 4, 100, 0.025, 140.0, 0.0, 0.0);
	// pidForward(M_PI / 4, {{90, 113}, {91, 114}}, 100, 0.5, 100, 20, 20, 0, 0, 0, 0, 0, 0, true);
	pros::Task intakeController2(stopIntakesAsync, NULL, "Intake Controller");
	// pros::delay(250);
	indexerFunctions.shootTwoBalls(NULL);
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
	pidBackward(M_PI / 4, {{66, 111}, {64, 110}}, 100, 0.5, 100, 15, 20, 0, 0, 0, 0, 0, 0, true);
	indexerFunctions.toggleIntakes(127);
	pidTurn(M_PI, 100, 0.025, 120.0, 0.0, 0.0);
	pros::Task poopController(indexerFunctions.poopTwoBalls, (void *)true, "Poop Controller");
	pidForward(M_PI, {{64, 105}, {64, 56.5}}, 100, 0.5, 100, 15, -30, 0, 0, 0, 0, 0, 0, true);
	pidTurn(3 * M_PI / 2, 100, 0.025, 140.0, 0.0, 0.0);
	indexerFunctions.toggleIntakes(0);
	pidForward(3 * M_PI / 2, {{62, 53.5}, {53, 53.5}}, 127, 0.5, 100, 50, -20, 0, 0, 0, 0, 0, 0, true);
	leftBackMotor = -63;
	leftFrontMotor = -63;
	rightFrontMotor = -63;
	rightBackMotor = -63;
	pros::delay(1000);
	pidForward(3 * M_PI / 2, {{62, 53.5}, {53, 53.5}}, 127, 0.5, 100, 50, -20, 0, 0, 0, 0, 0, 0, true);
	leftBackMotor = -63;
	leftFrontMotor = -63;
	rightFrontMotor = -63;
	rightBackMotor = -63;
	pros::delay(1000);
	pidForward(3 * M_PI / 2, {{62, 54}, {53, 54}}, 127, 0.5, 100, 50, -20, 0, 0, 0, 0, 0, 0, true);
	leftBackMotor = -63;
	leftFrontMotor = -63;
	rightFrontMotor = -63;
	rightBackMotor = -63;
	pros::delay(600);

	// pidBackward(3 * M_PI / 2, { {53, 55.5}, {62, 55.5} }, 127, 0.5, 100, 50, 20, 0, 0, 0, 0, 0, 0, true);
	// pidForward(3 * M_PI / 2, { {62, 55.5}, {53, 55.5} }, 127, 0.5, 100, 50, -20, 0, 0, 0, 0, 0, 0, true);
	// pidBackward(3 * M_PI / 2, { {53, 55.5}, {62, 55.5} }, 127, 0.5, 100, 50, 20, 0, 0, 0, 0, 0, 0, true);
	// pidForward(3 * M_PI / 2, { {62, 55.5}, {53, 55.5} }, 127, 0.5, 100, 50, -20, 0, 0, 0, 0, 0, 0, true);
	// pidBackward(3 * M_PI / 2, { {53, 55.5}, {62, 55.5} }, 127, 0.5, 100, 50, 20, 0, 0, 0, 0, 0, 0, true);

	indexerFunctions.toggleIntakes(127);

	// leftBackMotor = 80;
	// leftFrontMotor = 80;
	// rightFrontMotor = 80;
	// rightBackMotor = 80;
	// pros::delay(600);
	// leftBackMotor = 0;
	// leftFrontMotor = 0;
	// rightFrontMotor = 0;
	// rightBackMotor = 0;
	// leftBackMotor = -63;
	// leftFrontMotor = -63;
	// rightFrontMotor = -63;
	// rightBackMotor = -63;
	// pros::delay(500);
	// leftBackMotor = 0;
	// leftFrontMotor = 0;
	// rightFrontMotor = 0;
	// rightBackMotor = 0;
}

/**
 * Route to score sixth goal
*/
void sixthGoal()
{
	// pidTurn(M_PI / 2, 100, 0.025, 120.0, 0.0, 0.0);
	// //might need to be negative
	// pidLeft(M_PI / 2, {{60, 50}, {60, 66}}, 100, 0.5, 50, 10, 20, 0, 0, 0, 0, 0, 0, true);
	// pidForward(M_PI / 2, {{60, 66}, {85, 66}}, 100, 0.5, 100, 15, 30, 0, 0, 0, 0, 0, 0, true);

	pros::Task poopController(indexerFunctions.poopTwoBalls, (void *)true, "Poop Controller");
	//ppMove({{119, -69, M_PI / 2 + M_PI / 4}, {87, -40, 3*M_PI/2}}, 1, 0.00, 0.00, 0.001, 5.0, 10.0, 3.0, 10, 1.0, 28, 300, 0.08);
	indexerFunctions.toggleIntakes(127);
	//ppMove({{87, -40, 3*M_PI /2}, {65, -40, 3*M_PI/2}}, 1, 0.00, 0.00, 0.001, 5.0, 10.0, 3.0, 10, 1.0, 28, 100, 0.08);
	//ppMove({{65, -40, 3*M_PI/2}, {65, -66, M_PI}}, 1, 0.00, 0.00, 0.001, 5.0, 10.0, 3.0, 10, 1.0, 28, 300, 0.08);



	// pros::Task intakeController2(stopIntakesAsyncOne, NULL, "Intake Controller");

	pros::Task intakeController(stopIntakesAsync, NULL, "Intake Controller");
	indexerFunctions.shootTwoBalls(NULL);
	indexer.toggleTopPosition(true);

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
	pidBackward(M_PI / 2, {{83, 61}, {79, 61}}, 100, 0.5, 50, 20, 20, 0, 0, 0, 0, 0, 0, true);
	indexerFunctions.toggleIntakes(127);
	pidTurn(M_PI - .08, 100, 0.025, 120.0, 0.0, 0.0);
	pros::Task poopController(indexerFunctions.poopOneBall, (void *)true, "Poop Controller");
	// indexerFunctions.poopOneBall(NULL);
	// indexerFunctions.poopOneBall(NULL);
	// indexer.toggleTopPosition(false);

	pidForward(M_PI, {{78, 61}, {78, 24}}, 100, 0.5, 50, 20, -20, 0, 0, 0, 0, 0, 0, true);
	// pidBackward(M_PI, {{76, 18}, {76, 27}}, 80, 0.5, 50, 10, -20, 0, 0, 0, 0, 0, 0, true);
	pidTurn(M_PI / 2 + M_PI / 4, 100, 0.025, 120.0, 0.0, 0.0);
	pidForward(M_PI / 2 + M_PI / 4, {{96, 14}, {97, 13}}, 100, 0.5, 50, 40, 30, 0, 0, 0, 0, 0, 0, true);
	pros::Task intakeController(stopIntakesAsync, NULL, "Intake Controller");
	pros::delay(250);
	indexerFunctions.shootOneBall(NULL);
	indexer.toggleTopPosition(true);
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
	pidBackward(M_PI / 2 + M_PI / 4, {{96, 13}, {82, 27}}, 100, 0.5, 50, 10, 20, 0, 0, 0, 0, 0, 0, true);
	indexerFunctions.toggleIntakes(127);
	pidTurn(M_PI / 2, 100, 0.025, 120.0, 0.0, 0.0);
	pidForward(M_PI / 2, {{82, 29}, {92, 29}}, 100, 0.5, 50, 20, 20, 0, 0, 0, 0, 0, 0, true);
	// leftFrontMotor = -63;
	// leftBackMotor = -63;
	// rightFrontMotor = -63;
	// rightBackMotor = -63;
	// pros::delay(500);
	leftFrontMotor = 0;
	leftBackMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	pidTurn(M_PI, 100, 0.025, 120.0, 0.0, 0.0);
	pros::Task poopController(indexerFunctions.poopTwoBalls, (void *)true, "Poop Controller");
	leftFrontMotor = 63;
	leftBackMotor = 63;
	rightFrontMotor = 63;
	rightBackMotor = 63;
	pros::delay(500);
	leftFrontMotor = 0;
	leftBackMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	// indexerFunctions.toggleIntakes(127);
	// pidTurn(M_PI, 100, 0.025, 120.0, 0.0, 0.0);
	// indexerFunctions.poopTwoBalls((void*)false);
	pidRight(M_PI, {{88, 18}, {44, 18}}, 100, 0.5, 50, 10, 20, 0, 0, 0, 0, 0, 0, true);
	leftBackMotor = 63;
	leftFrontMotor = 63;
	rightFrontMotor = 63;
	rightBackMotor = 63;
	pros::delay(650);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	// pros::Task intakeController(stopIntakesAsync, NULL, "Intake Controller");
	indexerFunctions.shootOneBall(NULL);
	indexer.toggleTopPosition(true);
	// while (!intakeStatus)
	// {
	// 	pros::delay(10);
	// }
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
	pros::delay(300);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	pidTurn(2 * M_PI, 80, 0.025, 100.0, 0.0, 0.0);
	// indexerFunctions.poopOneBall((void *) true);
	pros::Task poopController(indexerFunctions.poopOneBall, (void *)true, "Poop Controller");
	// indexer.toggleTop(true);
	// indexer.toggleBottom(true);
	// upperStack = 100;
	// lowerStack = 127;
	indexerFunctions.toggleIntakes(127);
	pidForward(2 * M_PI, {{37, 20}, {37, 40}}, 63, 0.5, 50, 63, 20, 0, 0, 0, 0, 0, 0, true);
	indexerFunctions.shootPowerful(NULL);
	indexer.toggleTop(true);
	indexer.toggleBottom(true);
	upperStack = 127;
	lowerStack = 127;
	indexerFunctions.toggleIntakes(-127);
	// pros::delay(2000);
	// indexer.toggleTop(false);
	// indexer.toggleBottom(false);
	// upperStack = 127;
	// lowerStack = 127;
	// pros::delay(250);
	// indexerFunctions.toggleIntakes(-127);
	// pros::delay(250);
	pros::delay(500);
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
	// generatePath({{0, 0, 0}, {0, 10, 0}, {5, 15, M_PI/4}}, 1, 0.00, 0.00, 0.001, 5.0, 10.0, 3.0);

	// ppMove({{0, 0, 2*M_PI}, {0, 20, 2*M_PI}, {20, 40, M_PI/4}}, 1, 0.00, 0.00, 0.001, 5.0, 10.0, 3.0, 6, 0.25, 30, 100);

	ppMove({{0, 0, 0}, {0, 40, 0}}, 1, 0.00, 0.00, 0.001, 5.0, 10.0, 3.0, 6, 0.25, 0.008, 10, 100, 30, 20, 0, 0);

	// ppMove({{0, 0, 0}, {0, -40, M_PI/2+M_PI/4}}, 1, 0.00, 0.00, 0.001, 5.0, 10.0, 3.0, 6, 0.25, 30, 300, 0.008);

	// moveRobot({4	, 1, 0.01}, 100, 100, 200);
	// 	moveRobot({1, 4, 50}, 100, 100, 100);
	// moveRobot({-4, 1, 50}, 100, 100, 100);
	// moveRobot({-1, 4, 50}, 100, 100, 100);
	// moveRobot({1, -4, 50}, 100, 100, 100);
	// moveRobot({4, -1, 50}, 100, 100, 100);
	// moveRobot({-1, -4, 50}, 100, 100, 100);
	// moveRobot({-4, -1, 50}, 100, 100, 100);

	//firstGoal();
	//secondGoal();
	//thirdGoal();
	//fourthGoal();
	//fifthGoal();
	//sixthGoal();

	//leftFrontMotor.set_brake_mode(MOTOR_BRAKE_COAST);
	//leftBackMotor.set_brake_mode(MOTOR_BRAKE_COAST);
	//rightFrontMotor.set_brake_mode(MOTOR_BRAKE_COAST);
	//rightBackMotor.set_brake_mode(MOTOR_BRAKE_COAST);

	// descoreMiddle();
	// seventhGoal();
	// eighthGoal();
	// ninthGoal();
}
