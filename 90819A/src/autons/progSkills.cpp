#include "autons/progSkills.h"

void runProgSkills() {

	pidForwardBeta(12, 12, M_PI/4, 63, 0.5, 50, 20, 20, 0, 0, 0, 0, 0, 0);

	// while (true){	
	// 	printf("(%.3f, %.3f, %.3f)\n", position.getPosition()[0], position.getPosition()[1], position.getTheta()*180 / M_PI);
	// 	pros::delay(1000);
	// }

	// //pros::Task positionTask(getPosition, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Position Task
	// //move({{0.0, 0.0}, {-16.0, 16.0}, {-48.0, 20.0}}, 1.0, 0.15, 0.85, 0.001, 0.5, 0.67, 3.0, 5, 15.0, 1.25, 0, 0, 0.4);
	// //pros::delay(200);

	// intakeMotorLeft = 127;
	// intakeMotorRight = 127;
	// ppMoveForward({ {0.0, 0.0}, {0.0, 8.0}, {2.0, 15.0} }, 1.0, 0.15, 0.85, 0.001, 0.5, 0.67, 3.0, 5, 15.0, 1.25, 0, 0, 0.4);
	// pros::delay(100);
	// intakeMotorLeft = 0;
	// intakeMotorRight = 0;
	// upperStack = 127;
	// lowerStack = 127;
	// pros::delay(350);
	// upperStack = 0;
	// lowerStack = 0;

	// // pidForward(-6.0, -33.0, M_PI / 2, 80, 4, 220.0, 180.0);
	// // ppMoveRight({ getPosition(), {-16.0, -37.0} }, 1.0, 0.15, 0.85, 0.001, 0.5, 0.67, 3.0, 5, 15.0, 1.25, 0, 0, 0.2);

	// ppMoveBackward({ position.getPosition(), {-16.0, -36.0} }, 1.0, 0.15, 0.85, 0.001, 0.5, 0.67, 3.0, 5, 15.0, 1.25, 0, 0, 0.2);
	// pros::delay(200);
	// pidTurn(M_PI / 2, 80, 0.025, 200.0, 0.0, 0.0);
	// pros::delay(200);
	// pidForward(-7.0, position.getPosition()[1], M_PI / 2, 60, 1.5, 30.0, 200.0);
	// pros::delay(200);
	// upperStack = 127;
	// lowerStack = 127;
	// pros::delay(1000);
	// upperStack = 0;
	// lowerStack = 0;
	// ppMoveBackward({ position.getPosition(), {-24.0, -65.0} }, 1.0, 0.15, 0.85, 0.001, 0.5, 0.67, 3.0, 5, 15.0, 1.25, 0, 0, 0.1);
	// pidTurn(M_PI * 3 / 4, 80, 0.025, 180.0, 0.0, 0.0);
	// intakeMotorLeft = 127;
	// intakeMotorRight = 127;
	// pidForward(1.0, position.getPosition()[1], M_PI * 3.0 / 4, 60, 4, 220.0, 160.0);
	// pros::delay(250);
	// intakeMotorLeft = 0;
	// intakeMotorRight = 0;
	// upperStack = 127;
	// lowerStack = 127;
	// chassis->turnAngle(45_deg);
	// chassisStrafe->moveDistance(12_in);


	// pidTurn(M_PI / 2, 80, 0.025, 200.0, 0.0, 0.0);

	//pros::delay(200);
	//move({{-50.0, 10.0}}, 1.0, 0.15, 0.85, 0.001, 0.5, 1.0, 3.0, 5, 15.0, 1.25, 0, 0, 0.4);
}