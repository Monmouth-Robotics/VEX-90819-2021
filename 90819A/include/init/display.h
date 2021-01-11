#ifndef _DISPLAY
#define _DISPLAY

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
#include "positioning/positionController.h"

using namespace std;

class Display
{
public:
	Display();
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
	static lv_obj_t* text;
	static int autonCode;
	static lv_obj_t* xText;
	static lv_obj_t* yText;
	static lv_obj_t* thetaText;
	static bool positionDisplaySetup;
	static lv_style_t* style;
};



#endif
