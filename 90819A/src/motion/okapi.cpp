#include "motion/okapi.h"

const int DRIVE_MOTOR_LEFT_FRONT = 6;
const int DRIVE_MOTOR_LEFT_BACK = 19;
const int DRIVE_MOTOR_RIGHT_FRONT = 9;
const int DRIVE_MOTOR_RIGHT_BACK = 11;
const double WHEEL_DIAMETER = 3.25;
const double CHASSIS_WIDTH = 15.0;

std::shared_ptr<OdomChassisController> chassis = ChassisControllerBuilder()
													 .withMotors(DRIVE_MOTOR_LEFT_FRONT, DRIVE_MOTOR_RIGHT_FRONT, DRIVE_MOTOR_RIGHT_BACK, DRIVE_MOTOR_LEFT_BACK)
													 .withGains(
														 {0.001, 0, 0.0001}, // Distance controller gains
														 {0.001, 0, 0.0001}, // Turn controller gains
														 {0.001, 0, 0.0001}	 // Angle controller gains (helps drive straight)
														 )
													 .withDimensions(AbstractMotor::gearset::green, {{2.75_in, 6.75_in, 2.75_in, 2.75_in}, quadEncoderTPR})
													 .withSensors(ADIEncoder{'E', 'F', true}, ADIEncoder{'G', 'H', true}, ADIEncoder{'A', 'B', true})
													 .withOdometry()
													 .buildOdometry();

std::shared_ptr<ChassisController> chassisStrafe = ChassisControllerBuilder()
													   .withMotors(DRIVE_MOTOR_LEFT_FRONT, DRIVE_MOTOR_RIGHT_FRONT, DRIVE_MOTOR_RIGHT_BACK, DRIVE_MOTOR_LEFT_BACK)
													   .withGains(
														   {0.001, 0, 0.0001}, // Distance controller gains
														   {0.001, 0, 0.0001}, // Turn controller gains
														   {0.001, 0, 0.0001}  // Angle controller gains (helps drive straight)
														   )
													   .withDimensions(AbstractMotor::gearset::green, {{2.75_in, 6.75_in, 2.75_in, 2.75_in}, quadEncoderTPR})
													   .withSensors(ADIEncoder{'E', 'F', true}, ADIEncoder{'G', 'H', true}, ADIEncoder{'A', 'B', true})
													   .build();