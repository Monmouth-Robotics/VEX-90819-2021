#ifndef _DISPLAY
#define _DISPLAY

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
#include "positioning/positionController.h"
#include "macros/indexController.h"

using namespace std;

class Display
{
public:
	Display();
	static int getPrimaryAutonCode();
	static void initialize(void* ignore);
	
private:
	static void displayAuton();
	static void displayPosition();
	static void displayIndex();
	static lv_res_t resetButton_action(lv_obj_t* btn);
	static lv_res_t selectAuton(lv_obj_t* btn);
	static lv_obj_t* text;
	static int autonCode;
	static lv_obj_t* xText;
	static lv_obj_t* yText;
	static lv_obj_t* thetaText;
	static lv_obj_t* thetaText2;
	static lv_obj_t* topText;
	static lv_obj_t* bottomText;
	static lv_obj_t* intakeText;
	static lv_obj_t* resetButton;
	static bool positionDisplaySetup;
	static bool autonDisplaySetup;
	static bool indexDisplaySetup;
	static lv_style_t* style;
	static lv_obj_t* tabview;
	static lv_obj_t* tab1;
	static lv_obj_t* tab2;
	static lv_obj_t* tab3;
};



#endif
