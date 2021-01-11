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

//Stores whether or not position display has been setup
bool Display::positionDisplaySetup = false;

lv_style_t* Display::style = &lv_style_plain;

Display::Display() {
	
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
void Display::setAutonCode(int autonNum)
{
	if (autonNum == 1)
	{
		autonCode = 1;
		//Updates text on screen
		lv_label_set_text(text, "Current State: Blue Easy Autonomous");
	}
	else if (autonNum == 2)
	{
		autonCode = 2;
		//Updates text on screen
		lv_label_set_text(text, "Current State: Blue Hard Autonomous");
	}
	else if (autonNum == 3)
	{
		autonCode = 3;
		//Updates text on screen
		lv_label_set_text(text, "Current State: Red Easy Autonomous");
	}

	else if (autonNum == 4)
	{
		autonCode = 4;
		//Updates text on screen
		lv_label_set_text(text, "Current State: Red Hard Autonomous");
	}
	else if (autonNum == 5)
	{
		autonCode = 5;
		//Updates text on screen
		lv_label_set_text(text, "Current State: Programming Skills");
	}
	else if (autonNum == 6)
	{
		autonCode = 6;
		//Updates text on screen
		lv_label_set_text(text, "Current State: Driver Skills");
	}
}

/**
 * Sets auton code to 1 when button 1 is pressed
*/
lv_res_t Display::btn1_action(lv_obj_t* btn)
{
	setAutonCode(1);
	return LV_RES_OK;
}

/**
 * Sets auton code to 2 when button 2 is pressed
*/
lv_res_t Display::btn2_action(lv_obj_t* btn)
{
	setAutonCode(2);
	return LV_RES_OK;
}

/**
 * Sets auton code to 3 when button 3 is pressed
*/
lv_res_t Display::btn3_action(lv_obj_t* btn)
{
	setAutonCode(3);
	return LV_RES_OK;
}

/**
 * Sets auton code to 4 when button 4 is pressed
*/
lv_res_t Display::btn4_action(lv_obj_t* btn)
{
	setAutonCode(4);
	return LV_RES_OK;
}

/**
 * Sets auton code to 51 when button 5 is pressed
*/
lv_res_t Display::btn5_action(lv_obj_t* btn)
{
	setAutonCode(5);
	return LV_RES_OK;
}

/**
 * Sets auton code to 6 when button 6 is pressed
*/
lv_res_t Display::btn6_action(lv_obj_t* btn)
{
	setAutonCode(6);
	return LV_RES_OK;
}

/**
 * Displays buttons on screen
*/
void Display::displayInit(int startCode)
{
	pros::delay(200);

	//Declares the text object to display auton mode
	text = lv_label_create(lv_scr_act(), NULL);

	//Creates button 1
	lv_obj_t* btn1 = lv_btn_create(lv_scr_act(), NULL);
	//Places button 1 on screen at (100, 20)
	lv_obj_set_pos(btn1, 100, 20);
	//Sets the size of the button to 100px in the x-direction and 50px in the y-direction
	lv_obj_set_size(btn1, 100, 50);
	//Sets the action to run btn1_action() when button is pressed
	lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn1_action);

	//Creates the text for button 1
	lv_obj_t* label1 = lv_label_create(btn1, NULL);
	//Sets the text for the button 1
	lv_label_set_text(label1, "Blue Easy");

	//Creates button 2
	lv_obj_t* btn2 = lv_btn_create(lv_scr_act(), NULL);
	//Places button 2 on screen at (100, 100)
	lv_obj_set_pos(btn2, 100, 100);
	//Sets the size of the button to 100px in the x-direction and 50px in the y-direction
	lv_obj_set_size(btn2, 100, 50);
	//Sets the action to run btn2_action() when button is pressed
	lv_btn_set_action(btn2, LV_BTN_ACTION_CLICK, btn2_action);

	//Creates the text for button 2
	lv_obj_t* label2 = lv_label_create(btn2, NULL);
	//Sets the text for the button 2
	lv_label_set_text(label2, "Blue Hard");

	//Creates button 3
	lv_obj_t* btn3 = lv_btn_create(lv_scr_act(), NULL);
	//Places button 3 on screen at (300, 20)
	lv_obj_set_pos(btn3, 300, 20);
	//Sets the size of the button to 100px in the x-direction and 50px in the y-direction
	lv_obj_set_size(btn3, 100, 50);
	//Sets the action to run btn3_action() when button is pressed
	lv_btn_set_action(btn3, LV_BTN_ACTION_CLICK, btn3_action);

	//Creates the text for button 3
	lv_obj_t* label3 = lv_label_create(btn3, NULL);
	//Sets the text for the button 3
	lv_label_set_text(label3, "Red Easy");

	//Creates button 4
	lv_obj_t* btn4 = lv_btn_create(lv_scr_act(), NULL);
	//Places button 4 on screen at (300, 100)
	lv_obj_set_pos(btn4, 300, 100);
	//Sets the size of the button to 100px in the x-direction and 50px in the y-direction
	lv_obj_set_size(btn4, 100, 50);
	//Sets the action to run btn4_action() when button is pressed
	lv_btn_set_action(btn4, LV_BTN_ACTION_CLICK, btn4_action);

	//Creates the text for button 4
	lv_obj_t* label4 = lv_label_create(btn4, NULL);
	//Sets the text for the button 4
	lv_label_set_text(label4, "Red Hard");

	//Creates button 5
	lv_obj_t* btn5 = lv_btn_create(lv_scr_act(), NULL);
	//Places button 5 on screen at (50, 200)
	lv_obj_set_pos(btn5, 50, 200);
	//Sets the size of the button to 100px in the x-direction and 50px in the y-direction
	lv_obj_set_size(btn5, 180, 50);
	//Sets the action to run btn5_action() when button is pressed
	lv_btn_set_action(btn5, LV_BTN_ACTION_CLICK, btn5_action);

	//Creates the text for button 5
	lv_obj_t* label5 = lv_label_create(btn5, NULL);
	//Sets the text for the button 5
	lv_label_set_text(label5, "Programming Skills");

	//Creates button 6
	lv_obj_t* btn6 = lv_btn_create(lv_scr_act(), NULL);
	//Places button 6 on screen at (275, 200)
	lv_obj_set_pos(btn6, 275, 200);
	//Sets the size of the button to 100px in the x-direction and 50px in the y-direction
	lv_obj_set_size(btn6, 150, 50);
	//Sets the action to run btn6_action() when button is pressed
	lv_btn_set_action(btn6, LV_BTN_ACTION_CLICK, btn6_action);

	//Creates the text for button 6
	lv_obj_t* label6 = lv_label_create(btn6, NULL);
	//Sets the text for the button 6
	lv_label_set_text(label6, "Driver Skills");

	//Sets the auton mode text to the top left
	lv_obj_set_pos(text, 0, 0);

	//Sets the global variable and changes text
	setAutonCode(startCode);
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

void Display::displayPosition(void* ignore) {
	while (true) {
		if (!positionDisplaySetup) {
			style->text.color = LV_COLOR_WHITE;
			style->text.font = &lv_font_dejavu_20;

			//Initializes the text object to display x-coordinate
			xText = lv_label_create(lv_scr_act(), NULL);

			//Initializes the text object to display y-coordinate
			yText = lv_label_create(lv_scr_act(), NULL);

			//Initializes the text object to display theta
			thetaText = lv_label_create(lv_scr_act(), NULL);

			//Sets the x-coordinate text to the top left
			lv_obj_set_pos(xText, 5, 0);
			lv_label_set_style(xText, style);

			//Sets the y-coordinate text under previous text
			lv_obj_set_pos(yText, 5, 20);
			lv_label_set_style(yText, style);

			//Sets the theta text under previous text
			lv_obj_set_pos(thetaText, 5, 40);
			lv_label_set_style(thetaText, style);

			//Creates reset button
			lv_obj_t* resetButton = lv_btn_create(lv_scr_act(), NULL);
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
		string xString = ((string)("X:      ") + (string)(to_string(PositionController().getPosition()[0])));
		lv_label_set_text(xText, strcpy(new char[xString.length() + 1], xString.c_str()));

		//Displays the value of y
		string yString = ((string)("Y:      ") + (string)(to_string(PositionController().getPosition()[1])));
		lv_label_set_text(yText, strcpy(new char[yString.length() + 1], yString.c_str()));

		//Displays the value of theta
		string thetaString = ((string)("Theta: ") + (string)(to_string(PositionController().getTheta() * 180 / M_PI)));
		lv_label_set_text(thetaText, strcpy(new char[thetaString.length() + 1], thetaString.c_str()));

		pros::delay(10);
	}
}