#ifndef _POSITION_ALG
#define _POSITION_ALG

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
#include "devices.h"
#include <vector>

using namespace std;

void calcPosition(void);
vector<double> getPosition(void);
void resetGlobal(void);
double getTheta(void);

#endif
