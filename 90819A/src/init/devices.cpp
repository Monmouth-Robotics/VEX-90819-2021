#include "init/devices.h"

//Controllers
pros::Controller controller(CONTROLLER_MASTER);
pros::Controller controllerTwo(CONTROLLER_PARTNER);

//Drivetrain motors
pros::Motor leftFrontMotor(14, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor leftBackMotor(11, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor rightFrontMotor(17, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
pros::Motor rightBackMotor(20, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);

//Stack motors
pros::Motor lowerStack(1, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor upperStack(10, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);

//Intake motors
pros::Motor intakeMotorLeft(4, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor intakeMotorRight(7, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);

//Shaft encoders
pros::ADIEncoder leftEncoder('A', 'B', true);
pros::ADIEncoder rightEncoder('G', 'H', true);
pros::ADIEncoder backEncoder('E', 'F', true);

//Inertial sensors
pros::Imu imuLeft(5);
pros::Imu imuRight(6);
pros::Imu imuCenter(13);

//Ultrasonic range finders
pros::ADIUltrasonic ultrasonicTopUpper({ {2, 'A', 'B'} });
pros::ADIUltrasonic ultrasonicTopLower({ {2, 'C', 'D'} });
pros::ADIUltrasonic ultrasonicBottomUpper({ {2, 'E', 'F'} });
pros::ADIUltrasonic ultrasonicBottomLower({ {2, 'G', 'H'} });

//Optical sensors
pros::Optical opticalSensor(9);

//Limit switches
pros::ADIDigitalIn limitSwitch('D');
pros::ADIDigitalIn limitSwitchTop('C');





