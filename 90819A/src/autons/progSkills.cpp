#include "autons/progSkills.h"

void runProgSkills() {

	// pidRight(0, 24, M_PI*3/2, 63, 0.5, 50, 50, 20, 0, 0, 0, 0, 0, 0, true);

	pidForward(5, 24, 0, { {0,0},{5,5} }, 63, 0.5, 50, 50, 20, 0, 0, 0, 0, 0, 0, true);


	//pidForward(0, 24, 0, 127, 0.25, 50, 20, 20, 0, 0, 0, 0, 0, 0, true);
	//pidTurn(3*M_PI/2-M_PI/4, 160, 0.025, 120.0, 0.0, 0.0);
	//printf("Angle: %.3f\n", position.getTheta()*180/M_PI);
	//intakeMotorLeft = 127;
	//intakeMotorRight = 127;
	//pidForward(-16, 8, 3*M_PI/2-M_PI/4, 80, 0.5, 50, 15, 30, 0, 0, 0, 0, 0, 0, true);
	//upperStack = 127;
	//lowerStack = 127;
	//pros::delay(1000);
	//pidBackward(0, 24, 3.92, 63, 0.5, 50, 63, 20, 0, 0, 0, 0, 0, 0, true);
	//pidTurn(M_PI*3/2, 160, 0.025, 100.0, 0.0, 0.0);
	//pidForward(-16, 24, M_PI*3/2, 63, 0.5, 50, 50, 20, 0, 0, 0, 0, 0, 0, true);
	//pidTurn(0.135, 90, 0.025, 100.0, 0.0, 0.0);
	//pidForward(-10, 58, 0.135, 63, 0.5, 50, 50, 20, 0, 0, 0, 0, 0, 0, true);
	//pidTurn(M_PI*3/2, 160, 0.025, 100.0, 0.0, 0.0);
	//// pidForward(-12, 60, 0.135, 80, 1.0, 0, 50, 5, 0, 0, 0, 0, 0, 0, true);
	//pidBackward(0, 26, 3*M_PI_2 +M_PI/6, 127, 0.5, 200, 20, 20, 0, 0, 0, 0, 0, 0, false);
	//pidTurn(0.221, 160, 0.025, 100.0, 0.0, 0.0);
	//pidForward(12, 58, 0.221, 63, 0.5, 50, 50, 20, 0, 0, 0, 0, 0, 0, false);
	//pidTurn(M_PI*3/2+M_PI/4, 160, 0.025, 100.0, 0.0, 0.0);
	//pidForward(-25, 85, M_PI*3/2+M_PI/4, 40, 0.5, 50, 20, 50, 0, 0, 0, 0, 0, 1, true);











	// pidForward(-12, 24, 4.71, 63, 0.5, 50, 20, 20, 0, 0, 0, 0, 0, 0, true);



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

	// // pidForwardOld(-6.0, -33.0, M_PI / 2, 80, 4, 220.0, 180.0);
	// // ppMoveRight({ getPosition(), {-16.0, -37.0} }, 1.0, 0.15, 0.85, 0.001, 0.5, 0.67, 3.0, 5, 15.0, 1.25, 0, 0, 0.2);

	// ppMoveBackward({ position.getPosition(), {-16.0, -36.0} }, 1.0, 0.15, 0.85, 0.001, 0.5, 0.67, 3.0, 5, 15.0, 1.25, 0, 0, 0.2);
	// pros::delay(200);
	// pidTurn(M_PI / 2, 80, 0.025, 200.0, 0.0, 0.0);
	// pros::delay(200);
	// pidForwardOld(-7.0, position.getPosition()[1], M_PI / 2, 60, 1.5, 30.0, 200.0);
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
	// pidForwardOld(1.0, position.getPosition()[1], M_PI * 3.0 / 4, 60, 4, 220.0, 160.0);
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