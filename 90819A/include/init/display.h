#ifndef _DISPLAY
#define _DISPLAY

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"

using namespace std;

void displayInit(int startCode);
void setAutonCode(int autonNum);
int getAutonCode();
void displayPosition(double x, double y, double theta);

#endif
