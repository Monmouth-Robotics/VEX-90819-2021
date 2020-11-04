#include "autons/progSkills.h"

void runProgSkills()
{

	// pidRight(0, 24, M_PI*3/2, 63, 0.5, 50, 50, 20, 0, 0, 0, 0, 0, 0, true);
	// pidForward(M_PI/4, {{12, 0}, {12, 24}}, 80, 0.5, 100, 50, 30, 0, 0, 0, 0, 0, 0, true);

	// pidRight(0, {{0, 0}, {24, 0}}, 63, 0.5, 50, 50, 30, 0, 0, 0, 0, 0, 0, true);

	intakeMotorLeft = 127;
	intakeMotorRight = 127;
	pidForward(0, {{0, 0}, {0, 24}}, 80, 0.25, 100, 20, 20, 0, 0, 0, 0, 0, 0, true);
	pidTurn(3*M_PI/2-M_PI/4, 80, 0.025, 120.0, 0.0, 0.0);
	// printf("Angle: %.3f\n", position.getTheta()*180/M_PI);
	
	pidForward(3*M_PI/2-M_PI/4, {{0, 24}, {-16, 8}}, 80, 0.5, 100, 20, 20, 0, 0, 0, 0, 0, 0, true);
	indexerFunctions.shootOneBall();
	indexerFunctions.shootOneBall();
	indexController.suspend();
	upperStack = -127;
	lowerStack = -127;
	intakeMotorLeft = -127;
	intakeMotorRight = -127;
	pidBackward(3.92, {{-16, 8}, {0, 24}}, 63, 0.5, 50, 63, 20, 0, 0, 0, 0, 0, 0, true);
	pidTurn(M_PI*3/2, 80, 0.025, 100.0, 0.0, 0.0);
	indexController.resume();
	intakeMotorLeft = 127;
	intakeMotorRight = 127;
	pidForward(M_PI*3/2, {{0,24}, {-16, 24}}, 63, 0.5, 50, 50, 20, 0, 0, 0, 0, 0, 0, true);
	pidTurn(0, 80, 0.025, 100.0, 0.0, 0.0);
	pidForward(0, {{-8,24}, {-8, 57}}, 80, 0.5, 30, 50, 50, 0, 0, 0, 0, 0, 0, true);
	pidTurn(M_PI*3/2, 80, 0.025, 100.0, 0.0, 0.0);
	leftBackMotor = 63;
	leftFrontMotor = 63;
	rightFrontMotor = 63;
	rightBackMotor = 63;
	pros::delay(350);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;


	intakeMotorRight = 0;
	intakeMotorLeft = 0;
	indexerFunctions.shootOneBall();
	indexerFunctions.shootOneBall();

	leftBackMotor = -63;
	leftFrontMotor = -63;
	rightFrontMotor = -63;
	rightBackMotor = -63;
	pros::delay(500);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	//start of part that doesnt work
	pidRight(3*M_PI/2, {{-5, 57}, {-5, 95}}, 80, 0.5, 200, 50, 20, 0, 0, 0, 0, 0, 0, true);
	intakeMotorLeft = 127;
	intakeMotorRight = 127;
	pidForward(3*M_PI/2, {{-5, 95}, {-13, 95}}, 63, 0.5, 100, 50, 20, 0, 0, 0, 0, 0, 0, true);
	pidBackward(3*M_PI/2, {{-13, 96}, {0, 96}}, 63, 0.5, 200, 50, 20, 0, 0, 0, 0, 0, 0, true);
	// pros::delay(5000);
	intakeMotorLeft = 0;
	intakeMotorRight = 0;
	// pros::delay(5000);
	pidTurn(5.529, 80, 0.025, 100.0, 0.0, 0.0);
	// pros::delay(5000);
	pidForward(5.529, {{-6, 96}, {-14, 112}}, 80, 0.5, 100, 50, 20, 0, 0, 0, 0, 0, 0, true);
	indexerFunctions.shootOneBall();
	//end of part that doesnt work



		// pidRight(3*M_PI/2+M_PI/3, {{0, 106}, {-10, 116}}, 63, 0.5, 200, 50, 20, 0, 0, 0, 0, 0, 0, true);

	// pidRight(M_PI*3/2, {{0, 57}, {0, 110}}, 80, 0.5, 100, 50, 30, 0, 0, 0, 0, 0, 0, true);
	// pidForward(M_PI*3/2, {{0, 110}, {-16, 110}}, 80, 0.5, 100, 50, 30, 0, 0, 0, 0, 0, 0, true);

	// pidTurn(0.135, 90, 0.025, 100.0, 0.0, 0.0);
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