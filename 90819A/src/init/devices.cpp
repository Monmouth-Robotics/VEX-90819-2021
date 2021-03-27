#include "init/devices.h"

//Controllers
pros::Controller controller(CONTROLLER_MASTER);

//Drivetrain motors
pros::Motor leftFrontMotor(5, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor leftBackMotor(1, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor rightFrontMotor(15, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
pros::Motor rightBackMotor(11, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);

//Stack motors
pros::Motor lowerStack(18, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor upperStack(20, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);

//Intake motors
pros::Motor intakeMotorLeft(2, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor intakeMotorRight(12, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);

//Shaft encoders
pros::ADIEncoder leftEncoder('A', 'B', true);
pros::ADIEncoder rightEncoder('G', 'H', false);
pros::ADIEncoder backEncoder('C', 'D', false);

//Inertial sensors
pros::Imu imuLeft(10);
pros::Imu imuRight(8);
pros::Imu imuCenter(9);

//Optical sensors
pros::Optical opticalSensorTop(0);
pros::Optical opticalSensorIntake(0);

//Limit switches
pros::ADIDigitalIn limitSwitchLeft('E');
pros::ADIDigitalIn limitSwitchRight('F');
