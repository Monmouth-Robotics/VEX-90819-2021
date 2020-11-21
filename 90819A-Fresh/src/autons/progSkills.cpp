#include "autons/progSkills.h"

void firstGoal()
{
	intakeMotorLeft = 127;
	intakeMotorRight = 127;
	pidForward(0, {{0, 0}, {0, 24}}, 80, 0.25, 100, 20, 20, 0, 0, 0, 0, 0, 0, true);
	pidTurn(3 * M_PI / 2 - M_PI / 4, 80, 0.025, 120.0, 0.0, 0.0);
	pidForward(3 * M_PI / 2 - M_PI / 4, {{0, 24}, {-18, 8}}, 80, 0.5, 100, 20, -20, 0, 0, 0, 0, 0, 0, true);
	indexerFunctions.shootOneBall();
	indexerFunctions.shootOneBall();
	indexController.suspend();
}

void secondGoal()
{
	upperStack = -127;
	lowerStack = -127;
	intakeMotorLeft = -127;
	intakeMotorRight = -127;
	pidBackward(3.92, {{-20, 0}, {0, 24}}, 63, 0.5, 50, 63, -20, 0, 0, 0, 0, 0, 0, true);
	pidTurn(M_PI * 3 / 2, 80, 0.025, 100.0, 0.0, 0.0);
	indexController.resume();
	intakeMotorLeft = 127;
	intakeMotorRight = 127;
	pidForward(M_PI * 3 / 2, {{0, 27}, {-16, 27}}, 63, 0.5, 50, 50, -30, 0, 0, 0, 0, 0, 0, true);
	pidTurn(0, 80, 0.025, 100.0, 0.0, 0.0);
	pidForward(0, {{-7, 24}, {-7, 59}}, 80, 0.5, 30, 50, 50, 0, 0, 0, 0, 0, 0, true);
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
	intakeMotorRight = 0;
	intakeMotorLeft = 0;
	indexerFunctions.shootOneBall();
	indexerFunctions.shootOneBall();
}

void thirdGoal()
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
	pidRight(3 * M_PI / 2, {{-5, 57}, {-6, 96}}, 80, 0.5, 100, 50, 20, 0, 0, 0, 0, 0, 0, true);
	intakeMotorLeft = 127;
	intakeMotorRight = 127;
	pidForward(3 * M_PI / 2, {{-5, 99}, {-11, 100}}, 63, 0.5, 400, 50, -20, 0, 0, 0, 0, 0, 0, true);
	pros::delay(250);
	pidBackward(3 * M_PI / 2, {{-13, 99}, {6, 97}}, 63, 0.5, 400, 50, -20, 0, 0, 0, 0, 0, 0, true);
	intakeMotorLeft = 0;
	intakeMotorRight = 0;
	pidTurn(5.529, 127, 0.025, 100.0, 0.0, 0.0);
	pidForward(5.529, {{10, 99}, {-12, 116}}, 80, 0.5, 50, 20, -20, 0, 0, 0, 0, 0, 0, true);
	// pros::delay(250);
	indexerFunctions.shootOneBall();
}

void fourthGoal()
{
	pidBackward(5.76, {{-12, 115}, {12, 87}}, 80, 0.5, 50, 20, -50, 0, 0, 0, 0, 0, 0, true);
	pidTurn(M_PI / 2, 127, 0.025, 100.0, 0.0, 0.0);
	intakeMotorLeft = 127;
	intakeMotorRight = 127;
	pidForward(M_PI / 2, {{12, 85}, {40, 85}}, 80, 0.5, 100, 20, 10, 0, 0, 0, 0, 0, 0, true);
	pidTurn(0, 80, 0.025, 100.0, 0.0, 0.0);
	pidForward(0, {{40, 84}, {40, 111}}, 80, 0.5, 100, 20, 10, 0, 0, 0, 0, 0, 0, true);
	pros::delay(250);
	intakeMotorLeft = 0;
	intakeMotorRight = 0;
	indexerFunctions.shootOneBall();
}

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
	pidTurn(M_PI / 2, 80, 0.025, 100.0, 0.0, 0.0);
	intakeMotorRight = 127;
	intakeMotorLeft = 127;
	pidForward(M_PI / 2, {{41, 110}, {66, 110}}, 80, 0.5, 100, 20, 20, 0, 0, 0, 0, 0, 0, true);
	leftBackMotor = -63;
	leftFrontMotor = 63;
	rightFrontMotor = -63;
	rightBackMotor = 63;
	pros::delay(750);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	pidForward(M_PI / 2, {{80, 95}, {92, 95}}, 80, 0.5, 100, 20, 20, 0, 0, 0, 0, 0, 0, true);
	pros::delay(250);
	pidBackward(M_PI / 2, {{94, 95}, {73, 95}}, 80, 0.5, 100, 20, 20, 0, 0, 0, 0, 0, 0, true);
	pidTurn(M_PI / 4, 80, 0.025, 140.0, 0.0, 0.0);
	intakeMotorLeft = 0;
	intakeMotorRight = 0;
	pidForward(M_PI / 4, {{91, 113}, {92, 114}}, 80, 0.5, 100, 15, 20, 0, 0, 0, 0, 0, 0, true);
	pros::delay(250);
	indexerFunctions.shootOneBall();
	indexerFunctions.shootOneBall();
}

void descoreMiddle()
{
	pidBackward(M_PI / 2, {{92, 108}, {62, 108}}, 80, 0.5, 100, 20, 20, 0, 0, 0, 0, 0, 0, true);
	pidTurn(M_PI, 80, 0.025, 100.0, 0.0, 0.0);
	intakeMotorLeft = 127;
	intakeMotorRight = 127;
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

void sixthGoal()
{
	pidTurn(M_PI / 2, 80, 0.025, 100.0, 0.0, 0.0);
	intakeMotorLeft = 127;
	intakeMotorRight = 127;
	leftBackMotor = 63;
	leftFrontMotor = -63;
	rightFrontMotor = 63;
	rightBackMotor = -63;
	pros::delay(600);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	pidForward(M_PI / 2, {{60, 64}, {87, 64}}, 80, 0.5, 100, 15, 30, 0, 0, 0, 0, 0, 0, true);
	indexerFunctions.shootOneBall();
}

void seventhGoal()
{
	pidBackward(M_PI / 2, {{83, 61}, {73, 61}}, 80, 0.5, 50, 20, 20, 0, 0, 0, 0, 0, 0, true);
	pidTurn(M_PI, 80, 0.025, 100.0, 0.0, 0.0);

	pidForward(M_PI, {{76, 61}, {76, 18}}, 80, 0.5, 50, 10, -30, 0, 0, 0, 0, 0, 0, true);

	pidBackward(M_PI, {{76, 18}, {76, 27}}, 80, 0.5, 50, 10, -20, 0, 0, 0, 0, 0, 0, true);
	pidTurn(M_PI / 2 + M_PI / 4, 80, 0.025, 100.0, 0.0, 0.0);
	pidForward(M_PI / 2 + M_PI / 4, {{94, 12}, {95, 11}}, 80, 0.5, 50, 20, 30, 0, 0, 0, 0, 0, 0, true);
	indexerFunctions.shootOneBall();
}

void eighthGoal()
{
	pidBackward(M_PI / 2 + M_PI / 4, {{95, 12}, {88, 18}}, 80, 0.5, 50, 10, 20, 0, 0, 0, 0, 0, 0, true);
	pidTurn(M_PI, 80, 0.025, 100.0, 0.0, 0.0);
	pidRight(M_PI, {{88, 18}, {40, 18}}, 80, 0.5, 50, 10, 20, 0, 0, 0, 0, 0, 0, true);
	// pidForward(M_PI, {{36, 18}, {36, 12}}, 63, 0.5, 50, 20, -20, 0, 0, 0, 0, 0, 0, true);

	leftBackMotor = 63;
	leftFrontMotor = 63;
	rightFrontMotor = 63;
	rightBackMotor = 63;
	pros::delay(500);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	indexerFunctions.shootOneBall();
}

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
	pidTurn(2 * M_PI, 80, 0.025, 100.0, 0.0, 0.0);
	pidForward(2 * M_PI, {{36, 20}, {36, 43}}, 80, 0.5, 50, 20, 30, 0, 0, 0, 0, 0, 0, true);
	indexerFunctions.shootOneBall();
	pros::delay(250);
	intakeMotorLeft = -127;
	intakeMotorRight = -127;
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

	//middle goal descore

	//sixth goal

	//seventh goal

	//eight goal

	//ninth goal
}