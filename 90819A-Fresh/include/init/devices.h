#ifndef _DEVICES
#define _DEVICES

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"

extern pros::Controller controller;

extern pros::Motor leftFrontMotor;
extern pros::Motor leftBackMotor;
extern pros::Motor rightFrontMotor;
extern pros::Motor rightBackMotor;

extern pros::Motor lowerStack;
extern pros::Motor upperStack;

extern pros::Motor intakeMotorLeft;
extern pros::Motor intakeMotorRight;

extern pros::ADIEncoder leftEncoder;
extern pros::ADIEncoder rightEncoder;
extern pros::ADIEncoder backEncoder;

extern pros::Optical opticalSensor;

extern pros::ADIUltrasonic ultrasonicTopOne;
extern pros::ADIUltrasonic ultrasonicTopTwo;
extern pros::ADIUltrasonic ultrasonicBottomOne;
extern pros::ADIUltrasonic ultrasonicBottomTwo;
extern pros::ADIUltrasonic ultrasonicBack;

extern pros::Imu imuLeft;
extern pros::Imu imuRight;

extern pros::ADIAnalogIn lineSensor;

#endif