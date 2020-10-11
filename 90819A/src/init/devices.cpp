#include "init/devices.h"

pros::Controller controller(CONTROLLER_MASTER);

pros::Motor leftFrontMotor(13, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor leftBackMotor(15, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor rightFrontMotor(17, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
pros::Motor rightBackMotor(16, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);

pros::Motor lowerStack(12, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor upperStack(21, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
pros::Motor intakeMotorLeft(11, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor intakeMotorRight(19, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);

pros::ADIEncoder leftEncoder('E', 'F', true);
pros::ADIEncoder rightEncoder('G', 'H', true);
pros::ADIEncoder backEncoder('A', 'B', true);
pros::ADIAnalogIn lineSensorTop ('C');
pros::ADIAnalogIn lineSensorBottom ('D');