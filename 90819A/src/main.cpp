#include "main.h"


using namespace std;

#define _USE_MATH_DEFINES

lv_obj_t *text = lv_label_create(lv_scr_act(), NULL);
int autonCode = 5;

void setAutonState()
{
    if (autonCode == 1)
    {
        lv_label_set_text(text, "Current State: Blue Easy Autonomous");
    }
    else if (autonCode == 2)
    {
        lv_label_set_text(text, "Current State: Blue Hard Autonomous");
    }
    else if (autonCode == 3)
    {
        lv_label_set_text(text, "Current State: Red Easy Autonomous");
    }

    else if (autonCode == 4)
    {
        lv_label_set_text(text, "Current State: Red Hard Autonomous");
    }
    else if (autonCode == 5)
    {
        lv_label_set_text(text, "Current State: Programming Skills");
    }
    else if (autonCode == 6)
    {
        lv_label_set_text(text, "Current State: Driver Skills");
    }
}

lv_res_t btn1_action(lv_obj_t *btn)
{
    autonCode = 1;
    setAutonState();
    return LV_RES_OK;
}

lv_res_t btn2_action(lv_obj_t *btn)
{
    autonCode = 2;
    setAutonState();
    return LV_RES_OK;
}

lv_res_t btn3_action(lv_obj_t *btn)
{
    autonCode = 3;
    setAutonState();
    return LV_RES_OK;
}

lv_res_t btn4_action(lv_obj_t *btn)
{
    autonCode = 4;
    setAutonState();
    return LV_RES_OK;
}

lv_res_t btn5_action(lv_obj_t *btn)
{
    autonCode = 5;
    setAutonState();
    return LV_RES_OK;
}

lv_res_t btn6_action(lv_obj_t *btn)
{
    autonCode = 6;
    setAutonState();
    return LV_RES_OK;
}

void initialize()
{
    pros::lcd::initialize();
}

void disabled() {
	resetGlobal();
}


void competition_initialize()
{
    pros::delay(200);
    lv_obj_t *btn1 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_pos(btn1, 100, 20);
    lv_obj_set_size(btn1, 100, 50);
    lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn1_action);

    lv_obj_t *label1 = lv_label_create(btn1, NULL);
    lv_label_set_text(label1, "Blue Easy");

    lv_obj_t *btn2 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_pos(btn2, 100, 100);
    lv_obj_set_size(btn2, 100, 50);
    lv_btn_set_action(btn2, LV_BTN_ACTION_CLICK, btn2_action);

    lv_obj_t *label2 = lv_label_create(btn2, NULL);
    lv_label_set_text(label2, "Blue Hard");

    lv_obj_t *btn3 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_pos(btn3, 300, 20);
    lv_obj_set_size(btn3, 100, 50);
    lv_btn_set_action(btn3, LV_BTN_ACTION_CLICK, btn3_action);

    lv_obj_t *label3 = lv_label_create(btn3, NULL);
    lv_label_set_text(label3, "Red Easy");

    lv_obj_t *btn4 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_pos(btn4, 300, 100);
    lv_obj_set_size(btn4, 100, 50);
    lv_btn_set_action(btn4, LV_BTN_ACTION_CLICK, btn4_action);

    lv_obj_t *label4 = lv_label_create(btn4, NULL);
    lv_label_set_text(label4, "Red Hard");

    lv_obj_t *btn5 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_pos(btn5, 50, 200);
    lv_obj_set_size(btn5, 180, 50);
    lv_btn_set_action(btn5, LV_BTN_ACTION_CLICK, btn5_action);

    lv_obj_t *label5 = lv_label_create(btn5, NULL);
    lv_label_set_text(label5, "Programming Skills");

    lv_obj_t *btn6 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_pos(btn6, 275, 200);
    lv_obj_set_size(btn6, 150, 50);
    lv_btn_set_action(btn6, LV_BTN_ACTION_CLICK, btn6_action);

    lv_obj_t *label6 = lv_label_create(btn6, NULL);
    lv_label_set_text(label6, "Driver Skills");

    lv_obj_set_pos(text, 0, 0); /*Set its position*/

    setAutonState();
}

void autonomous()
{
    leftFrontMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
    leftBackMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
    rightFrontMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
    rightBackMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);

    leftEncoder.reset();
    rightEncoder.reset();
    backEncoder.reset();
    resetGlobal();

    //pros::Task positionTask(getPosition, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Position Task
    //move({{0.0, 0.0}, {-16.0, 16.0}, {-48.0, 20.0}}, 1.0, 0.15, 0.85, 0.001, 0.5, 0.67, 3.0, 5, 15.0, 1.25, 0, 0, 0.4);
    //pros::delay(200);
    intakeMotorLeft = 127;
    intakeMotorRight = 127;
    ppMoveForward({{0.0, 0.0}, {0.0, 8.0}, {2.0, 15.0}}, 1.0, 0.15, 0.85, 0.001, 0.5, 0.67, 3.0, 5, 15.0, 1.25, 0, 0, 0.4);
    pros::delay(500);
    upperStack = 127;
    lowerStack = 127;
    pros::delay(350);
    upperStack = 0;
    lowerStack = 0;
    ppMoveBackward({getPosition(), {-16.0, -33.0}}, 1.0, 0.15, 0.85, 0.001, 0.5, 0.67, 3.0, 5, 15.0, 1.25, 0, 0, 0.2);
    pros::delay(200);
    pidTurn(M_PI / 2, 80, 0.025, 180.0,0.0,0.0);
    upperStack = 127;
    lowerStack = 127;
    pros::delay(500);
    upperStack = 0;
    lowerStack = 0;
    //pros::delay(20000);
    printf("here");
    ppMoveBackward({getPosition(), {-11.0, -79.0}}, 1.0, 0.15, 0.85, 0.001, 0.5, 0.67, 3.0, 5, 15.0, 1.25, 0, 0, 0.4);
    pidTurn(M_PI*3/4, 80, 0.025, 180.0,0.0,0.0);

    //pros::delay(200);
    //move({{-50.0, 10.0}}, 1.0, 0.15, 0.85, 0.001, 0.5, 1.0, 3.0, 5, 15.0, 1.25, 0, 0, 0.4);
}

void moveDrive(int motorSpeed, int turnSpeed, int strafeSpeed)
{
    //forward: all positive
    //right: lF and rB positive, lB and rF negative
    //back: all negative
    //left: lB and rF positive, lF and rB negative

    if (abs(motorSpeed) > 20 && abs(turnSpeed) > 20 && abs(strafeSpeed) > 20)
    {
        leftFrontMotor = motorSpeed + turnSpeed + strafeSpeed;
        leftBackMotor = motorSpeed + turnSpeed - strafeSpeed;
        rightFrontMotor = motorSpeed - turnSpeed - strafeSpeed;
        rightBackMotor = motorSpeed - turnSpeed + strafeSpeed;
    }
    else if (abs(motorSpeed) > 20 && abs(turnSpeed) > 20)
    {
        leftFrontMotor = motorSpeed + turnSpeed;
        leftBackMotor = motorSpeed + turnSpeed;
        rightFrontMotor = motorSpeed - turnSpeed;
        rightBackMotor = motorSpeed - turnSpeed;
    }
    else if (abs(motorSpeed) > 20 && abs(strafeSpeed) > 20)
    {
        leftFrontMotor = motorSpeed + strafeSpeed;
        leftBackMotor = motorSpeed - strafeSpeed;
        rightFrontMotor = motorSpeed - strafeSpeed;
        rightBackMotor = motorSpeed + strafeSpeed;
    }
    else if (abs(turnSpeed) > 20 && abs(strafeSpeed) > 20)
    {
        leftFrontMotor = strafeSpeed + turnSpeed;
        leftBackMotor = -strafeSpeed + turnSpeed;
        rightFrontMotor = -strafeSpeed - turnSpeed;
        rightBackMotor = strafeSpeed - turnSpeed;
    }
    else if (abs(motorSpeed) > 20)
    {
        leftFrontMotor = motorSpeed;
        leftBackMotor = motorSpeed;
        rightFrontMotor = motorSpeed;
        rightBackMotor = motorSpeed;
    }
    else if (abs(turnSpeed) > 20)
    {
        leftFrontMotor = turnSpeed;
        leftBackMotor = turnSpeed;
        rightFrontMotor = -turnSpeed;
        rightBackMotor = -turnSpeed;
    }
    else if (abs(strafeSpeed) > 20)
    {
        leftFrontMotor = strafeSpeed;
        leftBackMotor = -strafeSpeed;
        rightFrontMotor = -strafeSpeed;
        rightBackMotor = strafeSpeed;
    }
    else
    {
        leftFrontMotor = 0;
        leftBackMotor = 0;
        rightFrontMotor = 0;
        rightBackMotor = 0;
    }
}

void opcontrol()
{
    // Break type for all motors
    leftFrontMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    leftBackMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    rightFrontMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    rightBackMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    //lowerStack.set_brake_mode(MOTOR_BRAKE_BRAKE);
    //upperStack.set_brake_mode(MOTOR_BRAKE_BRAKE);
    //intakeMotorRight.set_brake_mode(MOTOR_BRAKE_BRAKE);
    //intakeMotorLeft.set_brake_mode(MOTOR_BRAKE_BRAKE);

    while (true)
    {
        getPosition();
        printf("Theta: %.3f\n", getTheta() * 180 / M_PI);
        printf("X: %.3f\n", getPosition()[0]);
        printf("Y: %.3f\n\n", getPosition()[1]);
        //resetGlobal();
        //printf("Left: %.3f\n", leftEncoder.get_value()* M_PI / 180.0 * WHEEL_DIAMETER /2);
        //printf("Right: %.3f\n", rightEncoder.get_value()* M_PI / 180.0 * WHEEL_DIAMETER /2);
        //printf("Back: %.3f\n", backEncoder.get_value()* M_PI / 180.0 * WHEEL_DIAMETER /2);

        int motorSpeed = controller.get_analog(ANALOG_LEFT_Y);
        int strafeSpeed = controller.get_analog(ANALOG_LEFT_X);
        int turnSpeed = controller.get_analog(ANALOG_RIGHT_X);

        if (turnSpeed > 100)
            turnSpeed = 127;
        else if (turnSpeed < -100)
            turnSpeed = -127;

        moveDrive(motorSpeed, turnSpeed, strafeSpeed);

        if (controller.get_digital(DIGITAL_B))
        {
            intakeMotorLeft = 0;
            intakeMotorRight = 0;
        }

        else if (controller.get_digital(DIGITAL_A))
        {
            intakeMotorLeft = 127;
            intakeMotorRight = 127;
        }
        else if (controller.get_digital(DIGITAL_Y))
        {
            intakeMotorLeft = -127;
            intakeMotorRight = -127;
        }

        else if (controller.get_digital(DIGITAL_X))
        {
            upperStack = -127;
            lowerStack = -127;
        }

        if (controller.get_digital(DIGITAL_L1))
        {
            upperStack = 127;
        }

        else if (controller.get_digital(DIGITAL_L2))
        {
            upperStack = 0;
        }

        if (controller.get_digital(DIGITAL_R1))
        {
            lowerStack = 80;
        }

        else if (controller.get_digital(DIGITAL_R2))
        {
            lowerStack = 0;
        }

        if (controller.get_digital(DIGITAL_LEFT))
        {
            upperStack = -127;
        }

        pros::delay(10);
    }
}