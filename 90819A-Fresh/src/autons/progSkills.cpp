#include "autons/progSkills.h"

void runProgSkills()
{

	// first goal
	intakeMotorLeft = 127;
	intakeMotorRight = 127;
	pidForward(0, {{0, 0}, {0, 24}}, 80, 0.25, 100, 20, 20, 0, 0, 0, 0, 0, 0, true);
	pidTurn(3*M_PI/2-M_PI/4, 80, 0.025, 120.0, 0.0, 0.0);	
	pidForward(3*M_PI/2-M_PI/4, {{0, 24}, {-18, 8}}, 80, 0.5, 100, 20, -20, 0, 0, 0, 0, 0, 0, true);
	indexerFunctions.shootOneBall();
	indexerFunctions.shootOneBall();
	indexController.suspend();

	// second goal
	upperStack = -127;
	lowerStack = -127;
	intakeMotorLeft = -127;
	intakeMotorRight = -127;
	pidBackward(3.92, {{-20, 0}, {0, 24}}, 63, 0.5, 50, 63, -20, 0, 0, 0, 0, 0, 0, true);
	pidTurn(M_PI*3/2, 80, 0.025, 100.0, 0.0, 0.0);
	indexController.resume();
	intakeMotorLeft = 127;
	intakeMotorRight = 127;
	pidForward(M_PI*3/2, {{0,27}, {-16, 27}}, 63, 0.5, 50, 50, -20, 0, 0, 0, 0, 0, 0, true);
	pidTurn(0, 80, 0.025, 100.0, 0.0, 0.0);
	pidForward(0, {{-8,24}, {-9, 59}}, 80, 0.5, 30, 50, -50, 0, 0, 0, 0, 0, 0, true);
	pidTurn(M_PI*3/2, 80, 0.025, 100.0, 0.0, 0.0);
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

	//third goal
	leftBackMotor = -63;
	leftFrontMotor = -63;
	rightFrontMotor = -63;
	rightBackMotor = -63;
	pros::delay(500);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	pidRight(3*M_PI/2, {{-5, 57}, {-6, 96}}, 80, 0.5, 100, 50, 20, 0, 0, 0, 0, 0, 0, true);
	intakeMotorLeft = 127;
	intakeMotorRight = 127;
	pidForward(3*M_PI/2, {{-5, 99}, {-11, 100}}, 63, 0.5, 400, 50, -20, 0, 0, 0, 0, 0, 0, true);
	pros::delay(250);
	pidBackward(3*M_PI/2, {{-13, 99}, {6, 97}}, 63, 0.5, 400, 50, -20, 0, 0, 0, 0, 0, 0, true);
	intakeMotorLeft = 0;
	intakeMotorRight = 0;
	pidTurn(5.529, 127, 0.025, 100.0, 0.0, 0.0);
	pidForward(5.529, {{10, 99}, {-12, 116}}, 80, 0.5, 50, 20, -20, 0, 0, 0, 0, 0, 0, true);
	// pros::delay(250);
	indexerFunctions.shootOneBall();

	//fourth goal
	pidBackward(5.529, {{-12, 115}, {13, 84}}, 80, 0.5, 50, 20, -50, 0, 0, 0, 0, 0, 0, true);
	pidTurn(M_PI/2, 127, 0.025, 100.0, 0.0, 0.0);
	intakeMotorLeft = 127;
	intakeMotorRight = 127;
	pidForward(M_PI/2, {{12, 84}, {40, 84}}, 80, 0.5, 100, 20, 10, 0, 0, 0, 0, 0, 0, true);
	pidTurn(0, 80, 0.025, 100.0, 0.0, 0.0);
	pidForward(0, {{42, 84}, {42, 111}}, 80, 0.5, 100, 20, 10, 0, 0, 0, 0, 0, 0, true);
	pros::delay(250);
	intakeMotorLeft = 0;
	intakeMotorRight = 0;
	indexerFunctions.shootOneBall();

	//fifth goal
	leftBackMotor = -63;
	leftFrontMotor = -63;
	rightFrontMotor = -63;
	rightBackMotor = -63;
	pros::delay(500);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	pidTurn(M_PI/2, 80, 0.025, 100.0, 0.0, 0.0);
	intakeMotorRight = 127;
	intakeMotorLeft = 127;
	pidForward(M_PI/2, {{41, 102}, {70, 102}}, 80, 0.5, 100, 20, 20, 0, 0, 0, 0, 0, 0, true);
	leftBackMotor = -63;
	leftFrontMotor = 63;
	rightFrontMotor = -63;
	rightBackMotor = 63;
	pros::delay(750);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	pidForward(M_PI/2, {{94, 84}, {94, 95}}, 80, 0.5, 100, 20, 20, 0, 0, 0, 0, 0, 0, true);
	pros::delay(250);
	pidBackward(M_PI/2, {{94, 95}, {73, 95}}, 80, 0.5, 100, 20, 20, 0, 0, 0, 0, 0, 0, true);
	pidTurn(M_PI/4, 80, 0.025, 100.0, 0.0, 0.0);
	intakeMotorLeft = 0;
	intakeMotorRight = 0;
	pidForward(M_PI/4, {{90, 113}, {92, 114}}, 80, 0.5, 100, 15, 20, 0, 0, 0, 0, 0, 0, true);
	pros::delay(250);
	indexerFunctions.shootOneBall();
	indexerFunctions.shootOneBall();

	//middle goal descore
	pidBackward(M_PI/2, {{92, 108}, {62, 108}}, 80, 0.5, 100, 20, 20, 0, 0, 0, 0, 0, 0, true);
	pidTurn(M_PI, 80, 0.025, 100.0, 0.0, 0.0);
	intakeMotorLeft = 127;
	intakeMotorRight = 127;
	pidForward(M_PI, {{64, 105}, {64, 55}}, 80, 0.5, 100, 15, -30, 0, 0, 0, 0, 0, 0, true);
	pidTurn(3*M_PI/2, 80, 0.025, 140.0, 0.0, 0.0);
	leftBackMotor = 63;
	leftFrontMotor = 63;
	rightFrontMotor = 63;
	rightBackMotor = 63;
	pros::delay(750);
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


	//sixth goal
	pidTurn(M_PI/2, 80, 0.025, 100.0, 0.0, 0.0);
	intakeMotorLeft = 127;
	intakeMotorRight = 127;
	leftBackMotor = 63;
	leftFrontMotor = -63;
	rightFrontMotor = 63;
	rightBackMotor = -63;
	pros::delay(250);
	leftBackMotor = 0;
	leftFrontMotor = 0;
	rightFrontMotor = 0;
	rightBackMotor = 0;
	pidForward(M_PI/2, {{60, 60}, {90, 60}}, 80, 0.5, 100, 15, 30, 0, 0, 0, 0, 0, 0, true);
	indexerFunctions.shootOneBall();


	//seventh goal
	pidBackward(M_PI/2, {{83, 56}, {75, 21}}, 80, 0.5, 50, 20, 20, 0, 0, 0, 0, 0, 0, true);
	pidTurn(M_PI, 80, 0.025, 100.0, 0.0, 0.0);

	pidForward(M_PI, {{70, 56}, {70, 15}}, 80, 0.5, 50, 20, -30, 0, 0, 0, 0, 0, 0, true);

	pidBackward(M_PI, {{69, 15}, {69, 21}}, 80, 0.5, 50, 20, -20, 0, 0, 0, 0, 0, 0, true);
	pidTurn(M_PI/2+M_PI/4, 80, 0.025, 100.0, 0.0, 0.0);
	pidForward(M_PI/2 +M_PI/4, {{69, 21}, {89, 1}}, 80, 0.5, 50, 20, 15, 0, 0, 0, 0, 0, 0, true);
	indexerFunctions.shootOneBall();


	//eight goal
	// pidForward(M_PI, {{59, 56}, {59, 15}}, 80, 0.5, 100, 15, 60, 0, 0, 0, 0, 0, 0, true);

	//end of part that doesnt work
	//note to sai, I think the forward function is broken too, depending on the angle so all four functions need to be tested


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