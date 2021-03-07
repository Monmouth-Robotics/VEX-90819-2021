#include "init/devices.h"

//Controllers
pros::Controller controller(CONTROLLER_MASTER);

//Drivetrain motors
pros::Motor leftFrontMotor(15, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor leftBackMotor(4, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor rightFrontMotor(7, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
pros::Motor rightBackMotor(10, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);

//Stack motors
pros::Motor lowerStack(20, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor upperStack(12, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);

//Intake motors
pros::Motor intakeMotorLeft(18, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor intakeMotorRight(11, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);

//Shaft encoders
pros::ADIEncoder leftEncoder('A', 'B', true);
pros::ADIEncoder rightEncoder('G', 'H', true);
pros::ADIEncoder backEncoder('E', 'F', true);

//Inertial sensors
pros::Imu imuLeft(0);
pros::Imu imuRight(0);
pros::Imu imuCenter(0);

//Optical sensors
pros::Optical opticalSensorTop(0);
pros::Optical opticalSensorIntake(0);




