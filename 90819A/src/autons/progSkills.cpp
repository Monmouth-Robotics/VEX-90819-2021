#include "autons/progSkills.h"

bool intakeStatus = false;

/**
 * Stops intakes when two blue balls need to be descored
*/
void stopIntakesAsync(void* ignore)
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

	indexerFunctions.toggleIntakes(0);

}
void stopIntakesAsyncFast(void* ignore)
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

	while (indexer.getBottomStatus() == ""){
		pros::delay(10);
	}

	pros::delay(100);

	intakeStatus = true;

	indexerFunctions.toggleIntakes(-127);
	// //Outtakes until intakes no longer contain red ball
	// while (indexer.getIntakeColor() == "red")
	// {
	// 	indexerFunctions.toggleIntakes(-127);
	// }

	// indexerFunctions.toggleIntakes(0);

}


/**
 * Stops intakes when one blue ball needs to be descored
*/
void stopIntakesAsyncOne(void* ignore)
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
	indexerFunctions.deploy(NULL);
	// pros::Task deploy(indexerFunctions.deploy, NULL, "Robot Deploy");
	// indexerFunctions.toggleIntakes(127);
	pidForward(0, { {0, 0}, {0, 24} }, 127, 0.25, 50, 20, 20, 0, 0, 0, 0, 0, 0, true);
	pidTurn(3 * M_PI / 2-0.016, 127, 0.025, 120.0, 0.0, 0.0);
	pidForward(M_PI * 3 / 2, { {0, 27}, {-14, 27} }, 127, 0.5, 50, 50, -30, 0, 0, 0, 0, 0, 0, true);
	pros::delay(100);
	pidBackward(M_PI * 3 / 2, { {-14, 27}, {-6, 27} }, 127, 0.5, 50, 50, -30, 0, 0, 0, 0, 0, 0, true);
	pidTurn(3 * M_PI / 2 - M_PI/4, 127, 0.025, 120.0, 0.0, 0.0);
	pidForward(3 * M_PI / 2 - M_PI / 4, { {0, 24}, {-18, 10} }, 127, 0.5, 100, 20, -20, 0, 0, 0, 0, 0, 0, true);
	pros::Task intakeController(stopIntakesAsync, NULL, "Intake Controller");
	// indexerFunctions.shootOneBall(NULL);
	// indexerFunctions.shootTwoBalls(NULL);
	indexerFunctions.shootOneBall(NULL);
	pros::delay(100);
	indexerFunctions.shootOneBall(NULL);
	pros::delay(100);
	indexerFunctions.shootOneBall(NULL);

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
	pidBackward(3.66, { {-16, 8}, {12, 16} }, 100, 0.5, 50, 80, -20, 0, 0, 0, 0, 0, 0, true);
	indexerFunctions.toggleIntakes(127);
	pidTurn(2*M_PI - 0.175, 127, 0.025, 120.0, 0.0, 0.0);
	pros::Task poopController(indexerFunctions.poopTwoBalls, (void*)true, "Poop Controller");
	pidForward(0, { {12, 16}, {12, 59} }, 100, 0.5, 100, 30, 20, 0, 0, 0, 0, 0, 0, true);
	pidTurn(M_PI*3/2+0.008, 127, 0.025, 120.0, 0.0, 0.0);
	pidForward(M_PI*3/2, { {12, 63}, {-10, 63} }, 100, 0.5, 50, 20, -20, 0, 0, 0, 0, 0, 0, true);
	// pidForward(M_PI * 3 / 2, { {0, 27}, {-14, 27} }, 80, 0.5, 50, 50, -30, 0, 0, 0, 0, 0, 0, true);
	// pidTurn(0, 100, 0.025, 140.0, 0.0, 0.0);
	// indexerFunctions.poopOneBall(NULL);
	// pros::delay(500);
	// indexerFunctions.poopOneBall(NULL);
	// pros::Task intakeController(stopIntakesAsync, NULL, "Intake Controller");
	// pidForward(0, { {-12, 24}, {-12, 59} }, 100, 0.5, 30, 50, 50, 0, 0, 0, 0, 0, 0, true);
	// leftFrontMotor = 63;
	// leftBackMotor = -63;
	// rightFrontMotor = -63;
	// rightBackMotor = 63;
	// pros::delay(500);
	// leftFrontMotor = 0;
	// leftBackMotor = 0;
	// rightFrontMotor = 0;
	// rightBackMotor = 0;
	// pidTurn(M_PI * 3 / 2 - 0.008, 127, 0.025, 120.0, 0.0, 0.0);
	// leftBackMotor = 63;
	// leftFrontMotor = 63;
	// rightFrontMotor = 63;
	// rightBackMotor = 63;
	// pros::delay(500);
	// leftBackMotor = 0;
	// leftFrontMotor = 0;
	// rightFrontMotor = 0;
	// rightBackMotor = 0;
	pros::Task intakeController2(stopIntakesAsync, NULL, "Intake Controller2");
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
	leftBackMotor = -100;
	leftFrontMotor = -100;
	rightFrontMotor = -100;
	rightBackMotor = -100;
	pros::delay(400);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	indexerFunctions.toggleIntakes(127);
	indexer.toggleTopPosition(true);
	pidTurn(2 * M_PI, 100, 0.025, 120.0, 0.0, 0.0);
	pros::Task poopController(indexerFunctions.poopOneBall, (void*)true, "Poop Controller");
	pidForward(0, { {0, 60}, {0, 104} }, 100, 0.5, 50, 20, 20, 0, 0, 0, 0, 0, 0, true);
	// leftBackMotor = -63;
	// leftFrontMotor = -63;
	// rightFrontMotor = -63; 
	// rightBackMotor = -63;
	// pros::delay(500);
	// leftBackMotor = 0;
	// leftFrontMotor = 0;
	// rightFrontMotor = 0;
	// rightBackMotor = 0;
	pidTurn(5.529, 127, 0.025, 120.0, 0.0, 0.0);
	pidForward(5.529, { {-13, 115}, {-14, 116} }, 100, 0.5, 50, 20, -30, 0, 0, 0, 0, 0, 0, true);
	// pros::delay(250);
	// pros::delay(250);
	pros::Task intakeController2(stopIntakesAsync, NULL, "Intake Controller 2");
	// pros::delay(250);
	indexerFunctions.shootOneBall(NULL);
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
	pidBackward(5.76, { {-12, 115}, {0, 103} }, 100, 0.5, 50, 20, -50, 0, 0, 0, 0, 0, 0, true);
	indexerFunctions.toggleIntakes(127);
	pidTurn(3*M_PI / 2, 127, 0.025, 120.0, 0.0, 0.0);
	pidForward(M_PI * 3 / 2, { {0, 98}, {-14, 98} }, 100, 0.5, 50, 50, -30, 0, 0, 0, 0, 0, 0, true);
	pros::delay(250);
	pidBackward(5.76, { {-12, 115}, {12, 89} }, 100, 0.5, 100, 20, -20, 0, 0, 0, 0, 0, 0, true);
	pidTurn(M_PI / 2, 100, 0.025, 120.0, 0.0, 0.0);
	pros::Task poopController(indexerFunctions.poopTwoBalls, (void*)true, "Poop Controller");
	// indexerFunctions.poopOneBall(NULL);
	// pros::delay(500);
	// indexerFunctions.poopOneBall(NULL);
	pidForward(M_PI / 2, { {12, 87}, {40, 87} }, 100, 0.5, 100, 20, 10, 0, 0, 0, 0, 0, 0, true);
	pidTurn(0, 100, 0.025, 120.0, 0.0, 0.0);
	pidForward(0, { {39, 84}, {39, 108} }, 100, 0.5, 100, 20, 10, 0, 0, 0, 0, 0, 0, true);
	pros::Task intakeController2(stopIntakesAsync, NULL, "Intake Controller");
	indexerFunctions.shootTwoBalls(NULL);
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
	leftBackMotor = -100;
	leftFrontMotor = -100;
	rightFrontMotor = -100;
	rightBackMotor = -100;
	pros::delay(350);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	indexer.toggleTopPosition(true);
	pidTurn(M_PI / 2, 100, 0.025, 120.0, 0.0, 0.0);
	indexerFunctions.toggleIntakes(127);
	pros::Task poopController(indexerFunctions.poopOneBall, (void*)true, "Poop Controller");
	pidForward(M_PI / 2, { {41, 112}, {66, 112} }, 100, 0.5, 100, 20, 35, 0, 0, 0, 0, 0, 0, true);

	pidRight(M_PI / 2, { {75, 112}, {75, 98} }, 100, 0.5, 100, 20, 20, 0, 0, 0, 0, 0, 0, true);

	// leftBackMotor = -63;
	// leftFrontMotor = 63;
	// rightFrontMotor = -63;
	// rightBackMotor = 63;
	// pros::delay(500);
	// leftBackMotor = 0;
	// leftFrontMotor = 0;
	// rightFrontMotor = 0;
	// rightBackMotor = 0;
	pidForward(M_PI / 2, { {80, 98}, {89, 98} }, 100, 0.5, 100, 20, 20, 0, 0, 0, 0, 0, 0, true);
	pros::delay(250);
	pidBackward(M_PI / 2, { {94, 95}, {80, 95} }, 100, 0.5, 100, 20, 20, 0, 0, 0, 0, 0, 0, true);
	pidTurn(M_PI / 4, 100, 0.025, 140.0, 0.0, 0.0);
	pidForward(M_PI / 4, { {92, 114}, {93, 115} }, 100, 0.5, 100, 15, 20, 0, 0, 0, 0, 0, 0, true);
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
	pidBackward(M_PI / 4, { {67, 109}, {66, 108} }, 100, 0.5, 100, 15, 20, 0, 0, 0, 0, 0, 0, true);
	indexerFunctions.toggleIntakes(127);
	pidTurn(M_PI-0.08, 100, 0.025, 120.0, 0.0, 0.0);
	pros::Task poopController(indexerFunctions.poopTwoBalls, (void*)true, "Poop Controller");
	pidForward(M_PI, { {64, 105}, {64, 57} }, 100, 0.5, 75, 15, -30, 0, 0, 0, 0, 0, 0, true);
	pidTurn(3 * M_PI / 2-0.1, 127, 0.025, 140.0, 0.0, 0.0);
	indexerFunctions.toggleIntakes(0);
	pidForward(3 * M_PI / 2, { {62, 53.5}, {53.5, 53.5} }, 127, 0.5, 100, 70, -20, 0, 0, 0, 0, 0, 0, true);
	leftBackMotor = -63;
	leftFrontMotor = -63;
	rightFrontMotor = -63;
	rightBackMotor = -63;
	pros::delay(500);
	pidForward(3 * M_PI / 2, { {62, 53.5}, {53.5, 53.5} }, 127, 0.5, 100, 70, -20, 0, 0, 0, 0, 0, 0, true);
	leftBackMotor = -63;
	leftFrontMotor = -63;
	rightFrontMotor = -63;
	rightBackMotor = -63;
	pros::delay(600);
	pidForward(3 * M_PI / 2, { {62, 53.5}, {53.5, 53.5} }, 127, 0.5, 100, 70, -20, 0, 0, 0, 0, 0, 0, true);
	leftBackMotor = -80;
	leftFrontMotor = -80;
	rightFrontMotor = -80;
	rightBackMotor = -80;
	pros::delay(400);
	
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
	pidTurn(M_PI / 2, 100, 0.025, 120.0, 0.0, 0.0);
	//might need to be negative
	pidLeft(M_PI / 2, { {60, 50}, {60, 65} }, 100, 0.5, 50, 10, 20, 0, 0, 0, 0, 0, 0, true);
	pidForward(M_PI / 2, { {60, 65}, {85, 65} }, 100, 0.5, 100, 15, 30, 0, 0, 0, 0, 0, 0, true);
	// pros::Task intakeController2(stopIntakesAsyncOne, NULL, "Intake Controller");

	pros::Task intakeController(stopIntakesAsync, NULL, "Intake Controller");
	indexerFunctions.shootOneBall(NULL);
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
	pidBackward(M_PI / 2, { {83, 61}, {76, 61} }, 100, 0.5, 50, 20, 20, 0, 0, 0, 0, 0, 0, true);
	indexerFunctions.toggleIntakes(127);
	pidTurn(M_PI-.16, 100, 0.025, 120.0, 0.0, 0.0);
	pros::Task poopController(indexerFunctions.poopOneBall, (void*)false, "Poop Controller");
	// indexerFunctions.poopOneBall(NULL);
	// indexerFunctions.poopOneBall(NULL);
	// indexer.toggleTopPosition(false);

	pidForward(M_PI, { {78, 61}, {78, 25} }, 100, 0.5, 50, 20, -20, 0, 0, 0, 0, 0, 0, true);
	// pidBackward(M_PI, {{76, 18}, {76, 27}}, 80, 0.5, 50, 10, -20, 0, 0, 0, 0, 0, 0, true);
	pidTurn(M_PI / 2 + M_PI / 4, 100, 0.025, 120.0, 0.0, 0.0);
	pidForward(M_PI / 2 + M_PI / 4, { {95, 15}, {96, 14} }, 100, 0.5, 50, 30, 40, 0, 0, 0, 0, 0, 0, true);
	pros::Task intakeController(stopIntakesAsync, NULL, "Intake Controller");
	pros::delay(100);
	indexerFunctions.shootTwoBalls(NULL);
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
	pidBackward(M_PI / 2 + M_PI / 4, { {96, 13}, {82, 27} }, 100, 0.5, 50, 10, 20, 0, 0, 0, 0, 0, 0, true);
	indexerFunctions.toggleIntakes(127);
	pidTurn(M_PI /2, 100, 0.025, 120.0, 0.0, 0.0);
	pidForward(M_PI / 2, { {82, 29}, {94, 29} }, 100, 0.5, 50, 20, 20, 0, 0, 0, 0, 0, 0, true);
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
	pros::Task poopController(indexerFunctions.poopTwoBalls, (void*)true, "Poop Controller");
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
	pidRight(M_PI, { {88, 18}, {45, 18} }, 100, 0.5, 50, 10, 20, 0, 0, 0, 0, 0, 0, true);
	leftBackMotor = 80;
	leftFrontMotor = 80;
	rightFrontMotor = 80;
	rightBackMotor = 80;
	pros::delay(600);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	pros::Task intakeController(stopIntakesAsync, NULL, "Intake Controller");
	indexerFunctions.shootOneBall(NULL);
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
	pros::delay(300);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	indexer.toggleTopPosition(true);
	pidTurn(2 * M_PI-0.008, 80, 0.025, 100.0, 0.0, 0.0);
	// indexerFunctions.poopOneBall((void *) true);
	pros::Task poopController(indexerFunctions.poopOneBall, (void*)true, "Poop Controller");
	// indexer.toggleTop(true);
	// indexer.toggleBottom(true);
	// upperStack = 100;
	// lowerStack = 127;
	indexerFunctions.toggleIntakes(127);
	pidForward(2 * M_PI, { {36, 20}, {36, 41}}, 90, 0.5, 50, 63, 30, 0, 0, 0, 0, 0, 0, true);
	indexerFunctions.shootOneBall(NULL);
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
