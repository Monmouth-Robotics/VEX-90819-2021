#include "init/display.h"

//Sets default auton mode
int Display::autonCode = 2;
int Display::autonCode2 = 0;

//Declares the text objects
lv_obj_t* Display::xText;
lv_obj_t* Display::yText;
lv_obj_t* Display::thetaText;
lv_obj_t* Display::thetaText2;
lv_obj_t* Display::topText;
lv_obj_t* Display::bottomText;
lv_obj_t* Display::intakeText;
lv_obj_t* Display::selectAutonText;

lv_obj_t* Display::resetButton;
lv_obj_t* Display::autonList;
lv_obj_t* Display::autonOptionsList;

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
	tabview = lv_tabview_create(lv_scr_act(), NULL);
	tab1 = lv_tabview_add_tab(tabview, "Auton Selection");
	tab2 = lv_tabview_add_tab(tabview, "Odometry");
	tab3 = lv_tabview_add_tab(tabview, "Indexing");
}

void Display::initialize(void* ignore) {
	while (true) {
		displayAuton();
		displayPosition();
		displayIndex();
		pros::delay(10);
	}
}

/**
 * Returns auton code
*/
int Display::getPrimaryAutonCode()
{
	return autonCode;
}

lv_res_t Display::selectAuton(lv_obj_t* btn)
{
	autonCode = lv_list_get_btn_index(autonList, btn);
	updateText();
	return LV_RES_OK;
}

lv_res_t Display::selectAutonOptions(lv_obj_t* btn)
{
	autonCode2 = lv_list_get_btn_index(autonOptionsList, btn);
	updateText();
	return LV_RES_OK;
}

void Display::updateText() {
	switch (autonCode) {
	case 0:
		switch (autonCode2) {
		case 0:
			lv_label_set_text(selectAutonText, "Selected:\nRed 1");
			break;
		case 1:
			lv_label_set_text(selectAutonText, "Selected:\nRed 2");
			break;
		case 2:
			lv_label_set_text(selectAutonText, "Selected:\nRed 3");
			break;
		}
		break;
	case 1:
		switch (autonCode2) {
		case 0:
			lv_label_set_text(selectAutonText, "Selected:\nBlue 1");
			break;
		case 1:
			lv_label_set_text(selectAutonText, "Selected:\nBlue 2");
			break;
		case 2:
			lv_label_set_text(selectAutonText, "Selected:\nBlue 3");
			break;
		}
		break;
	case 2:
		switch (autonCode2) {
		case 0:
			lv_label_set_text(selectAutonText, "Selected:\nProg 1");
			break;
		case 1:
			lv_label_set_text(selectAutonText, "Selected:\nProg 2");
			break;
		case 2:
			lv_label_set_text(selectAutonText, "Selected:\nProg 3");
			break;
		}
		break;
	}
}

/**
 * Displays buttons on screen
*/
void Display::displayAuton()
{
	if (!autonDisplaySetup) {
		selectAutonText = lv_label_create(tab1, NULL);
		updateText();
		lv_obj_align(selectAutonText, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);

		lv_obj_set_pos(selectAutonText, 150, 0);

		autonList = lv_list_create(tab1, NULL);
		lv_obj_set_size(autonList, 130, 150);

		lv_obj_align(autonList, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
		/*Add list elements*/
		lv_list_add(autonList, SYMBOL_PLAY, "Red", selectAuton);
		lv_list_add(autonList, SYMBOL_PLAY, "Blue", selectAuton);
		lv_list_add(autonList, SYMBOL_PLAY, "Prog", selectAuton);

		autonOptionsList = lv_list_create(tab1, NULL);
		lv_obj_set_size(autonOptionsList, 130, 150);
		lv_obj_align(autonOptionsList, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 0);

		lv_list_add(autonOptionsList, SYMBOL_PLAY, "1", selectAutonOptions);
		lv_list_add(autonOptionsList, SYMBOL_PLAY, "2", selectAutonOptions);
		lv_list_add(autonOptionsList, SYMBOL_PLAY, "3", selectAutonOptions);


		/*lv_obj_t* roller1 = lv_roller_create(tab1, NULL);
		lv_roller_set_options(roller1,
			"Red\n"
			"Blue\n"
			"Prog\n"
			"Driver");
		lv_roller_set_visible_row_count(roller1, 5);
		lv_roller_set_action(roller1, selectAuton);
		lv_obj_set_pos(roller1, 0, 0);
		lv_roller_set_selected(roller1, 2, true);*/
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
		xText = lv_label_create(tab2, NULL);

		//Initializes the text object to display y-coordinate
		yText = lv_label_create(tab2, NULL);

		//Initializes the text object to display theta
		thetaText = lv_label_create(tab2, NULL);
		thetaText2 = lv_label_create(tab2, NULL);

		//Sets the x-coordinate text to the top left
		lv_obj_set_pos(xText, 5, 20);
		lv_label_set_style(xText, style);

		//Sets the y-coordinate text under previous text
		lv_obj_set_pos(yText, 5, 40);
		lv_label_set_style(yText, style);

		//Sets the theta text under previous text
		lv_obj_set_pos(thetaText, 5, 60);
		lv_label_set_style(thetaText, style);
		lv_obj_set_pos(thetaText2, 5, 80);
		lv_label_set_style(thetaText2, style);

		//Creates reset button
		resetButton = lv_btn_create(tab2, NULL);
		//Places reset button on screen at (100, 100)
		lv_obj_set_pos(resetButton, 200, 110);
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

		topText = lv_label_create(tab3, NULL);

		bottomText = lv_label_create(tab3, NULL);

		intakeText = lv_label_create(tab3, NULL);

		lv_obj_set_pos(topText, 5, 40);
		lv_label_set_style(topText, style);

		lv_obj_set_pos(bottomText, 5, 60);
		lv_label_set_style(bottomText, style);

		lv_obj_set_pos(intakeText, 5, 80);
		lv_label_set_style(intakeText, style);

		indexDisplaySetup = true;
	}

	string topString = ((string)("Top:    ") + (string)(IndexController().getTopColor()));
	lv_label_set_text(topText, strcpy(new char[topString.length() + 1], topString.c_str()));

	string intakeString = ((string)("Intake: ") + (string)(IndexController().getIntakeColor()));
	lv_label_set_text(intakeText, strcpy(new char[intakeString.length() + 1], intakeString.c_str()));
}