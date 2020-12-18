#ifndef _DISPLAY
#define _DISPLAY

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "init/taskManagement.h"
#include "api.h"

using namespace std;

class Display
{
public:
	static void displayInit(int startCode);
	static void setAutonCode(int autonNum);
	static int getAutonCode();
	static void displayPosition(void* ignore);
private:
	static lv_res_t btn1_action(lv_obj_t* btn);
	static lv_res_t btn2_action(lv_obj_t* btn);
	static lv_res_t btn3_action(lv_obj_t* btn);
	static lv_res_t btn4_action(lv_obj_t* btn);
	static lv_res_t btn5_action(lv_obj_t* btn);
	static lv_res_t btn6_action(lv_obj_t* btn);
	static lv_res_t resetButton_action(lv_obj_t* btn);
};



#endif
