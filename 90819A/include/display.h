#ifndef _DISPLAY
#define _DISPLAY

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"

void displayInit(int startCode);
void setAutonCode(int autonNum);
int getAutonCode();

#endif
