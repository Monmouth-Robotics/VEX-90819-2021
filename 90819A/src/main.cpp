#include "main.h"

using namespace std;

#define _USE_MATH_DEFINES

lv_obj_t* text2 = lv_label_create(lv_scr_act(), NULL); /*Add a button the current screen*/

int autonCode2 = 5;

lv_res_t btn1_action2(lv_obj_t* btn)
{
	autonCode2 = 1;
	if (autonCode2 == 1)
	{
		lv_label_set_text(text2, "Current State: Blue Easy Autonomous");
	}
	else if (autonCode2 == 2)
	{
		lv_label_set_text(text2, "Current State: Blue Hard Autonomous");
	}
	else if (autonCode2 == 3)
	{
		lv_label_set_text(text2, "Current State: Red Easy Autonomous");
	}
	else if (autonCode2 == 4)
	{
		lv_label_set_text(text2, "Current State: Red Hard Autonomous");
	}
	else if (autonCode2 == 5)
	{
		lv_label_set_text(text2, "Current State: Programming Skills");
	}
	else if (autonCode2 == 6)
	{
		lv_label_set_text(text2, "Current State: Driver Skills");
	}
	return LV_RES_OK;
}

lv_res_t btn2_action2(lv_obj_t* btn)
{
	autonCode2 = 2;
	if (autonCode2 == 1)
	{
		lv_label_set_text(text2, "Current State: Blue Easy Autonomous");
	}
	else if (autonCode2 == 2)
	{
		lv_label_set_text(text2, "Current State: Blue Hard Autonomous");
	}
	else if (autonCode2 == 3)
	{
		lv_label_set_text(text2, "Current State: Red Easy Autonomous");
	}
	else if (autonCode2 == 4)
	{
		lv_label_set_text(text2, "Current State: Red Hard Autonomous");
	}
	else if (autonCode2 == 5)
	{
		lv_label_set_text(text2, "Current State: Programming Skills");
	}
	else if (autonCode2 == 6)
	{
		lv_label_set_text(text2, "Current State: Driver Skills");
	}
	return LV_RES_OK;
}

lv_res_t btn3_action2(lv_obj_t* btn)
{
	autonCode2 = 3;
	if (autonCode2 == 1)
	{
		lv_label_set_text(text2, "Current State: Blue Easy Autonomous");
	}
	else if (autonCode2 == 2)
	{
		lv_label_set_text(text2, "Current State: Blue Hard Autonomous");
	}
	else if (autonCode2 == 3)
	{
		lv_label_set_text(text2, "Current State: Red Easy Autonomous");
	}
	else if (autonCode2 == 4)
	{
		lv_label_set_text(text2, "Current State: Red Hard Autonomous");
	}
	else if (autonCode2 == 5)
	{
		lv_label_set_text(text2, "Current State: Programming Skills");
	}
	else if (autonCode2 == 6)
	{
		lv_label_set_text(text2, "Current State: Driver Skills");
	}
	return LV_RES_OK;
}

lv_res_t btn4_action2(lv_obj_t* btn)
{
	autonCode2 = 4;
	if (autonCode2 == 1)
	{
		lv_label_set_text(text2, "Current State: Blue Easy Autonomous");
	}
	else if (autonCode2 == 2)
	{
		lv_label_set_text(text2, "Current State: Blue Hard Autonomous");
	}
	else if (autonCode2 == 3)
	{
		lv_label_set_text(text2, "Current State: Red Easy Autonomous");
	}
	else if (autonCode2 == 4)
	{
		lv_label_set_text(text2, "Current State: Red Hard Autonomous");
	}
	else if (autonCode2 == 5)
	{
		lv_label_set_text(text2, "Current State: Programming Skills");
	}
	else if (autonCode2 == 6)
	{
		lv_label_set_text(text2, "Current State: Driver Skills");
	}
	return LV_RES_OK;
}

lv_res_t btn5_action2(lv_obj_t* btn)
{
	autonCode2 = 5;
	if (autonCode2 == 1)
	{
		lv_label_set_text(text2, "Current State: Blue Easy Autonomous");
	}
	else if (autonCode2 == 2)
	{
		lv_label_set_text(text2, "Current State: Blue Hard Autonomous");
	}
	else if (autonCode2 == 3)
	{
		lv_label_set_text(text2, "Current State: Red Easy Autonomous");
	}
	else if (autonCode2 == 4)
	{
		lv_label_set_text(text2, "Current State: Red Hard Autonomous");
	}
	else if (autonCode2 == 5)
	{
		lv_label_set_text(text2, "Current State: Programming Skills");
	}
	else if (autonCode2 == 6)
	{
		lv_label_set_text(text2, "Current State: Driver Skills");
	}
	return LV_RES_OK;
}

lv_res_t btn6_action2(lv_obj_t* btn)
{
	autonCode2 = 6;
	if (autonCode2 == 1)
	{
		lv_label_set_text(text2, "Current State: Blue Easy Autonomous");
	}
	else if (autonCode2 == 2)
	{
		lv_label_set_text(text2, "Current State: Blue Hard Autonomous");
	}
	else if (autonCode2 == 3)
	{
		lv_label_set_text(text2, "Current State: Red Easy Autonomous");
	}
	else if (autonCode2 == 4)
	{
		lv_label_set_text(text2, "Current State: Red Hard Autonomous");
	}
	else if (autonCode2 == 5)
	{
		lv_label_set_text(text2, "Current State: Programming Skills");
	}
	else if (autonCode2 == 6)
	{
		lv_label_set_text(text2, "Current State: Driver Skills");
	}
	return LV_RES_OK;
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	//Initialize PROS LCD
	pros::lcd::initialize();

	//Calibrate inertial sensor
	imuLeft.reset();
	imuRight.reset();
	int time = pros::millis();
	int iter = 0;
	while (imuLeft.is_calibrating() || imuRight.is_calibrating())
	{
		printf("IMU calibrating... %d\n", iter);
		iter += 10;
		pros::delay(10);
	}
	//Should print about 2000 ms
	printf("IMU is done calibrating (took %d ms)\n", iter - time);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled()
{
	//Reset position to (0,0,0)
	position.resetGlobal();
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize()
{
	//Show auton selection screen with default set as programming skills
	//displayInit(5);

	pros::delay(200);
	lv_obj_t* btn1 = lv_btn_create(lv_scr_act(), NULL);        /*Add a button the current screen*/
	lv_obj_set_pos(btn1, 100, 20);                             /*Set its position*/
	lv_obj_set_size(btn1, 100, 50);                            /*Set its size*/
	lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn1_action2); /*Assign a callback to the button*/

	lv_obj_t* label1 = lv_label_create(btn1, NULL); /*Add a label to the button*/
	lv_label_set_text(label1, "Blue Easy");         /*Set the labels text*/

	lv_obj_t* btn2 = lv_btn_create(lv_scr_act(), NULL);        /*Add a button the current screen*/
	lv_obj_set_pos(btn2, 100, 100);                            /*Set its position*/
	lv_obj_set_size(btn2, 100, 50);                            /*Set its size*/
	lv_btn_set_action(btn2, LV_BTN_ACTION_CLICK, btn2_action2); /*Assign a callback to the button*/

	lv_obj_t* label2 = lv_label_create(btn2, NULL); /*Add a label to the button*/
	lv_label_set_text(label2, "Blue Hard");         /*Set the labels text*/

	lv_obj_t* btn3 = lv_btn_create(lv_scr_act(), NULL);        /*Add a button the current screen*/
	lv_obj_set_pos(btn3, 300, 20);                             /*Set its position*/
	lv_obj_set_size(btn3, 100, 50);                            /*Set its size*/
	lv_btn_set_action(btn3, LV_BTN_ACTION_CLICK, btn3_action2); /*Assign a callback to the button*/

	lv_obj_t* label3 = lv_label_create(btn3, NULL); /*Add a label to the button*/
	lv_label_set_text(label3, "Red Easy");          /*Set the labels text*/

	lv_obj_t* btn4 = lv_btn_create(lv_scr_act(), NULL);        /*Add a button the current screen*/
	lv_obj_set_pos(btn4, 300, 100);                            /*Set its position*/
	lv_obj_set_size(btn4, 100, 50);                            /*Set its size*/
	lv_btn_set_action(btn4, LV_BTN_ACTION_CLICK, btn4_action2); /*Assign a callback to the button*/

	lv_obj_t* label4 = lv_label_create(btn4, NULL); /*Add a label to the button*/
	lv_label_set_text(label4, "Red Hard");          /*Set the labels text*/

	lv_obj_t* btn5 = lv_btn_create(lv_scr_act(), NULL);        /*Add a button the current screen*/
	lv_obj_set_pos(btn5, 50, 200);                             /*Set its position*/
	lv_obj_set_size(btn5, 180, 50);                            /*Set its size*/
	lv_btn_set_action(btn5, LV_BTN_ACTION_CLICK, btn5_action2); /*Assign a callback to the button*/

	lv_obj_t* label5 = lv_label_create(btn5, NULL);  /*Add a label to the button*/
	lv_label_set_text(label5, "Programming Skills"); /*Set the labels text*/

	lv_obj_t* btn6 = lv_btn_create(lv_scr_act(), NULL);        /*Add a button the current screen*/
	lv_obj_set_pos(btn6, 275, 200);                            /*Set its position*/
	lv_obj_set_size(btn6, 150, 50);                            /*Set its size*/
	lv_btn_set_action(btn6, LV_BTN_ACTION_CLICK, btn6_action2); /*Assign a callback to the button*/

	lv_obj_t* label6 = lv_label_create(btn6, NULL); /*Add a label to the button*/
	lv_label_set_text(label6, "Driver Skills");     /*Set the labels text*/

	lv_obj_set_pos(text2, 0, 0); /*Set its position*/

	if (autonCode2 == 1)
	{
		lv_label_set_text(text2, "Current State: Blue Easy Autonomous");
	}
	else if (autonCode2 == 2)
	{
		lv_label_set_text(text2, "Current State: Blue Hard Autonomous");
	}
	else if (autonCode2 == 3)
	{
		lv_label_set_text(text2, "Current State: Red Easy Autonomous");
	}
	else if (autonCode2 == 4)
	{
		lv_label_set_text(text2, "Current State: Red Hard Autonomous");
	}
	else if (autonCode2 == 5)
	{
		lv_label_set_text(text2, "Current State: Programming Skills");
	}
	else if (autonCode2 == 6)
	{
		lv_label_set_text(text2, "Current State: Driver Skills");
	}
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{
	//Reset position to (0,0,0)
	position.resetGlobal();

	// printf("here\n");
	//Set brake modes for all motors
	leftFrontMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	leftBackMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	rightFrontMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	rightBackMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	lowerStack.set_brake_mode(MOTOR_BRAKE_HOLD);
	upperStack.set_brake_mode(MOTOR_BRAKE_HOLD);
	intakeMotorLeft.set_brake_mode(MOTOR_BRAKE_BRAKE);
	intakeMotorRight.set_brake_mode(MOTOR_BRAKE_BRAKE);

	//Reset encoder values
	leftEncoder.reset();
	rightEncoder.reset();
	backEncoder.reset();

	//Run auton according to selection screen
	switch (getAutonCode())
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		//Reference to autons/progSkills.cpp
		runProgSkills();
		break;
	case 6:
		break;
	}
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol()
{
	//Reference to driveControl.cpp
	driveControl();
}