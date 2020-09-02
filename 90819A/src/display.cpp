#include "display.h"

lv_obj_t* text = lv_label_create(lv_scr_act(), NULL);
int autonCode = 5;

int getAutonCode() {
    return autonCode;
}

void setAutonCode(int autonNum)
{
    if (autonNum == 1)
    {
        autonCode = 1;
        lv_label_set_text(text, "Current State: Blue Easy Autonomous");
    }
    else if (autonNum == 2)
    {
        autonCode = 2;
        lv_label_set_text(text, "Current State: Blue Hard Autonomous");
    }
    else if (autonNum == 3)
    {
        autonCode = 3;
        lv_label_set_text(text, "Current State: Red Easy Autonomous");
    }

    else if (autonNum == 4)
    {
        autonCode = 4;
        lv_label_set_text(text, "Current State: Red Hard Autonomous");
    }
    else if (autonNum == 5)
    {
        autonCode = 5;
        lv_label_set_text(text, "Current State: Programming Skills");
    }
    else if (autonNum == 6)
    {
        autonCode = 6;
        lv_label_set_text(text, "Current State: Driver Skills");
    }
}

lv_res_t btn1_action(lv_obj_t* btn)
{
    setAutonCode(1);
    return LV_RES_OK;
}

lv_res_t btn2_action(lv_obj_t* btn)
{
    setAutonCode(2);
    return LV_RES_OK;
}

lv_res_t btn3_action(lv_obj_t* btn)
{
    setAutonCode(3);
    return LV_RES_OK;
}

lv_res_t btn4_action(lv_obj_t* btn)
{
    setAutonCode(4);
    return LV_RES_OK;
}

lv_res_t btn5_action(lv_obj_t* btn)
{
    setAutonCode(5);
    return LV_RES_OK;
}

lv_res_t btn6_action(lv_obj_t* btn)
{
    setAutonCode(6);
    return LV_RES_OK;
}

void displayInit(int startCode) {
    pros::delay(200);
    lv_obj_t* btn1 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_pos(btn1, 100, 20);
    lv_obj_set_size(btn1, 100, 50);
    lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn1_action);

    lv_obj_t* label1 = lv_label_create(btn1, NULL);
    lv_label_set_text(label1, "Blue Easy");

    lv_obj_t* btn2 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_pos(btn2, 100, 100);
    lv_obj_set_size(btn2, 100, 50);
    lv_btn_set_action(btn2, LV_BTN_ACTION_CLICK, btn2_action);

    lv_obj_t* label2 = lv_label_create(btn2, NULL);
    lv_label_set_text(label2, "Blue Hard");

    lv_obj_t* btn3 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_pos(btn3, 300, 20);
    lv_obj_set_size(btn3, 100, 50);
    lv_btn_set_action(btn3, LV_BTN_ACTION_CLICK, btn3_action);

    lv_obj_t* label3 = lv_label_create(btn3, NULL);
    lv_label_set_text(label3, "Red Easy");

    lv_obj_t* btn4 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_pos(btn4, 300, 100);
    lv_obj_set_size(btn4, 100, 50);
    lv_btn_set_action(btn4, LV_BTN_ACTION_CLICK, btn4_action);

    lv_obj_t* label4 = lv_label_create(btn4, NULL);
    lv_label_set_text(label4, "Red Hard");

    lv_obj_t* btn5 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_pos(btn5, 50, 200);
    lv_obj_set_size(btn5, 180, 50);
    lv_btn_set_action(btn5, LV_BTN_ACTION_CLICK, btn5_action);

    lv_obj_t* label5 = lv_label_create(btn5, NULL);
    lv_label_set_text(label5, "Programming Skills");

    lv_obj_t* btn6 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_pos(btn6, 275, 200);
    lv_obj_set_size(btn6, 150, 50);
    lv_btn_set_action(btn6, LV_BTN_ACTION_CLICK, btn6_action);

    lv_obj_t* label6 = lv_label_create(btn6, NULL);
    lv_label_set_text(label6, "Driver Skills");

    lv_obj_set_pos(text, 0, 0); /*Set its position*/

    setAutonCode(startCode);
}