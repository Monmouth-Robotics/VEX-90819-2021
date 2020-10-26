#include "init/devices.h"

pros::Controller controller(CONTROLLER_MASTER);

pros::Motor leftFrontMotor(14, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor leftBackMotor(11, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor rightFrontMotor(17, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
pros::Motor rightBackMotor(20, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);

pros::Motor lowerStack(1, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor upperStack(10, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);

pros::Motor intakeMotorLeft(4, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor intakeMotorRight(7, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);

pros::ADIEncoder leftEncoder('A', 'B', true);
pros::ADIEncoder rightEncoder('G', 'H', false);
pros::ADIEncoder backEncoder('E', 'F', false);

pros::ADIAnalogIn lineSensorTop ('C');
pros::ADIAnalogIn lineSensorBottom ('D');