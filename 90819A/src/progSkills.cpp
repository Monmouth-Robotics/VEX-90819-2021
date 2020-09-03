#include "progSkills.h"

void runProgSkills() {
	// //pros::Task positionTask(getPosition, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Position Task
	// //move({{0.0, 0.0}, {-16.0, 16.0}, {-48.0, 20.0}}, 1.0, 0.15, 0.85, 0.001, 0.5, 0.67, 3.0, 5, 15.0, 1.25, 0, 0, 0.4);
	// //pros::delay(200);
	intakeMotorLeft = 127;
	intakeMotorRight = 127;
	ppMoveForward({ {0.0, 0.0}, {0.0, 8.0}, {2.0, 15.0} }, 1.0, 0.15, 0.85, 0.001, 0.5, 0.67, 3.0, 5, 15.0, 1.25, 0, 0, 0.4);
	pros::delay(500);
	upperStack = 127;
	lowerStack = 127;
	pros::delay(350);
	upperStack = 0;
	lowerStack = 0;
	// pidForward(-6.0, -33.0, M_PI / 2, 80, 4, 220.0, 180.0);
	// ppMoveRight({ getPosition(), {-16.0, -37.0} }, 1.0, 0.15, 0.85, 0.001, 0.5, 0.67, 3.0, 5, 15.0, 1.25, 0, 0, 0.2);

	ppMoveBackward({ position.getPosition(), {-16.0, -40.0} }, 1.0, 0.15, 0.85, 0.001, 0.5, 0.67, 3.0, 5, 15.0, 1.25, 0, 0, 0.2);
	pros::delay(200);
	pidTurn(M_PI / 2, 80, 0.025, 180.0, 0.0, 0.0);
	pros::delay(200);
	pidForward(-8.0, -40.0, M_PI / 2, 60, 4, 220.0, 160.0);
	pros::delay(400);
	upperStack = 127;
	lowerStack = 127;
	pros::delay(500);
	upperStack = 0;
	lowerStack = 0;
	//pros::delay(20000);
	printf("here");
	ppMoveBackward({ position.getPosition(), {-15.0, -80.0} }, 1.0, 0.15, 0.85, 0.001, 0.5, 0.67, 3.0, 5, 15.0, 1.25, 0, 0, 0.2);
	pidTurn(M_PI * 3 / 4, 80, 0.025, 180.0, 0.0, 0.0);
	pidForward(position.getPosition()[0]+3.0, position.getPosition()[1]-3.0, M_PI * 3.0 / 4, 60, 4, 220.0, 160.0);
	upperStack = 127;
	lowerStack = 127;
	pros::delay(1000);
	upperStack = 0;
	lowerStack = 0;

	// pidTurn(M_PI / 2, 80, 0.025, 200.0, 0.0, 0.0);

	//pros::delay(200);
	//move({{-50.0, 10.0}}, 1.0, 0.15, 0.85, 0.001, 0.5, 1.0, 3.0, 5, 15.0, 1.25, 0, 0, 0.4);
}