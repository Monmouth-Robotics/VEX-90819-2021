#include "init/display.h"

//Declares the text object to display auton mode
lv_obj_t* Display::text;

//Sets default auton mode
int Display::autonCode = 5;

//Declares the text object to display x-coordinate
lv_obj_t* Display::xText;

//Declares the text object to display y-coordinate
lv_obj_t* Display::yText;

//Declares the text object to display theta
lv_obj_t* Display::thetaText;
lv_obj_t* Display::thetaText2;

lv_obj_t* Display::topText;
lv_obj_t* Display::bottomText;
lv_obj_t* Display::intakeText;


lv_obj_t* Display::resetButton;
int Display::displayMode = 1;

//Stores whether or not position display has been setup
bool Display::positionDisplaySetup = false;
bool Display::autonDisplaySetup = false;
bool Display::indexDisplaySetup = false;

lv_style_t* Display::style = &lv_style_plain;

lv_obj_t* Display::tabview;

/*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
lv_obj_t* Display::tab1;
lv_obj_t* Display::tab2;
lv_obj_t* Display::tab3;


Display::Display() {
	//tabview = lv_tabview_create(lv_scr_act(), NULL);
	//tab1 = lv_tabview_add_tab(tabview, "Auton Selection");
	//tab2 = lv_tabview_add_tab(tabview, "Odometry");
	//tab3 = lv_tabview_add_tab(tabview, "Indexing");
}

void Display::initialize(void* ignore) {
	displayMenu();
	while (true) {
		if (displayMode == 1) {
			displayAuton();
		}
		else if (displayMode == 2) {
			displayPosition();
		}
		else if (displayMode == 3) {
			displayIndex();
		}
		pros::delay(10);
	}
}

void Display::displayMenu() {
	lv_obj_t* autonSelect = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_pos(autonSelect, 0, 0);
	lv_obj_set_size(autonSelect, 150, 30);
	lv_btn_set_action(autonSelect, LV_BTN_ACTION_CLICK, autonSelect_action);

	lv_obj_t* autoSelectLabel = lv_label_create(autonSelect, NULL);
	lv_label_set_text(autoSelectLabel, "Auton Selection");

	lv_obj_t* odomSelect = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_pos(odomSelect, 150, 0);
	lv_obj_set_size(odomSelect, 100, 30);
	lv_btn_set_action(odomSelect, LV_BTN_ACTION_CLICK, odomSelect_action);

	lv_obj_t* odomSelectLabel = lv_label_create(odomSelect, NULL);
	lv_label_set_text(odomSelectLabel, "Odometry");

	lv_obj_t* indexSelect = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_pos(indexSelect, 250, 0);
	lv_obj_set_size(indexSelect, 100, 30);
	lv_btn_set_action(indexSelect, LV_BTN_ACTION_CLICK, indexSelect_action);

	lv_obj_t* indexSelectLabel = lv_label_create(indexSelect, NULL);
	lv_label_set_text(indexSelectLabel, "Indexing");
}

lv_res_t Display::autonSelect_action(lv_obj_t* btn)
{
	autonDisplaySetup = false;
	displayMode = 1;
	lv_obj_clean(lv_scr_act());
	displayMenu();
	return LV_RES_OK;
}

lv_res_t Display::odomSelect_action(lv_obj_t* btn)
{
	positionDisplaySetup = false;
	displayMode = 2;
	lv_obj_clean(lv_scr_act());
	displayMenu();
	return LV_RES_OK;
}

lv_res_t Display::indexSelect_action(lv_obj_t* btn)
{
	indexDisplaySetup = false;
	displayMode = 3;
	lv_obj_clean(lv_scr_act());
	displayMenu();
	return LV_RES_OK;
}

/**
 * Returns auton code
*/
int Display::getAutonCode()
{
	return autonCode;
}

/**
 * Sets auton mode when button press is detected
*/
void Display::setAutonCode(string color, string mode)
{

}

/**
 * Sets auton code to 1 when button 1 is pressed
*/
lv_res_t Display::btn1_action(lv_obj_t* btn)
{
	return LV_RES_OK;
}

/**
 * Sets auton code to 2 when button 2 is pressed
*/
lv_res_t Display::btn2_action(lv_obj_t* btn)
{
	return LV_RES_OK;
}

/**
 * Sets auton code to 3 when button 3 is pressed
*/
lv_res_t Display::btn3_action(lv_obj_t* btn)
{
	return LV_RES_OK;
}

/**
 * Sets auton code to 4 when button 4 is pressed
*/
lv_res_t Display::btn4_action(lv_obj_t* btn)
{
	return LV_RES_OK;
}

/**
 * Sets auton code to 51 when button 5 is pressed
*/
lv_res_t Display::btn5_action(lv_obj_t* btn)
{
	return LV_RES_OK;
}

/**
 * Sets auton code to 6 when button 6 is pressed
*/
lv_res_t Display::btn6_action(lv_obj_t* btn)
{
	return LV_RES_OK;
}

/**
 * Displays buttons on screen
*/
void Display::displayAuton()
{
	if (!autonDisplaySetup) {

		

		autonDisplaySetup = true;
	}
}

/**
 * Resets coordinates of positioning to (0,0)
*/
lv_res_t Display::resetButton_action(lv_obj_t* btn)
{
	PositionController().resetGlobal();
	PositionController().setTheta(0);
	return LV_RES_OK;
}

void Display::displayPosition() {
	if (!positionDisplaySetup) {
		style->text.color = LV_COLOR_WHITE;
		style->text.font = &lv_font_dejavu_20;

		//Initializes the text object to display x-coordinate
		xText = lv_label_create(lv_scr_act(), NULL);

		//Initializes the text object to display y-coordinate
		yText = lv_label_create(lv_scr_act(), NULL);

		//Initializes the text object to display theta
		thetaText = lv_label_create(lv_scr_act(), NULL);
		thetaText2 = lv_label_create(lv_scr_act(), NULL);

		//Sets the x-coordinate text to the top left
		lv_obj_set_pos(xText, 5, 40);
		lv_label_set_style(xText, style);

		//Sets the y-coordinate text under previous text
		lv_obj_set_pos(yText, 5, 60);
		lv_label_set_style(yText, style);

		//Sets the theta text under previous text
		lv_obj_set_pos(thetaText, 5, 80);
		lv_label_set_style(thetaText, style);
		lv_obj_set_pos(thetaText2, 5, 100);
		lv_label_set_style(thetaText2, style);

		//Creates reset button
		resetButton = lv_btn_create(lv_scr_act(), NULL);
		//Places reset button on screen at (100, 100)
		lv_obj_set_pos(resetButton, 200, 150);
		//Sets the size of the button to 100px in the x-direction and 50px in the y-direction
		lv_obj_set_size(resetButton, 100, 50);
		//Sets the action to run resetPosition() when button is pressed
		lv_btn_set_action(resetButton, LV_BTN_ACTION_CLICK, resetButton_action);

		//Creates the text for reset button
		lv_obj_t* resetLabel = lv_label_create(resetButton, NULL);
		//Sets the text for the reset button
		lv_label_set_text(resetLabel, "RESET " SYMBOL_REFRESH);

		positionDisplaySetup = true;
	}

	//Displays the value of x
	string xString = ((string)("X:      ") + (string)(to_string(PositionController().getPosition()[0])) + (string)(" inches"));
	lv_label_set_text(xText, strcpy(new char[xString.length() + 1], xString.c_str()));

	//Displays the value of y
	string yString = ((string)("Y:      ") + (string)(to_string(PositionController().getPosition()[1])) + (string)(" inches"));
	lv_label_set_text(yText, strcpy(new char[yString.length() + 1], yString.c_str()));

	//Displays the value of theta
	string thetaString = ((string)("Theta: ") + (string)(to_string(PositionController().getTheta())) + (string)(" radians"));
	lv_label_set_text(thetaText, strcpy(new char[thetaString.length() + 1], thetaString.c_str()));

	//Displays the value of theta
	string thetaString2 = ((string)("Theta: ") + (string)(to_string(PositionController().getTheta() * 180 / M_PI)) + (string)(" degrees"));
	lv_label_set_text(thetaText2, strcpy(new char[thetaString2.length() + 1], thetaString2.c_str()));
}

void Display::displayIndex() {
	if (!indexDisplaySetup) {
		style->text.color = LV_COLOR_WHITE;
		style->text.font = &lv_font_dejavu_20;

		topText = lv_label_create(lv_scr_act(), NULL);

		bottomText = lv_label_create(lv_scr_act(), NULL);

		intakeText = lv_label_create(lv_scr_act(), NULL);

		lv_obj_set_pos(topText, 5, 40);
		lv_label_set_style(topText, style);

		lv_obj_set_pos(bottomText, 5, 60);
		lv_label_set_style(bottomText, style);

		lv_obj_set_pos(intakeText, 5, 80);
		lv_label_set_style(intakeText, style);

		indexDisplaySetup = true;
	}

	string topString = ((string)("Top:    ") + (string)(IndexController().getTopStatus()));
	lv_label_set_text(topText, strcpy(new char[topString.length() + 1], topString.c_str()));

	string bottomString = ((string)("Bottom: ") + (string)(IndexController().getBottomStatus()));
	lv_label_set_text(bottomText, strcpy(new char[bottomString.length() + 1], bottomString.c_str()));

	string intakeString = ((string)("Intake: ") + (string)(IndexController().getIntakeColor()));
	lv_label_set_text(intakeText, strcpy(new char[intakeString.length() + 1], intakeString.c_str()));
}