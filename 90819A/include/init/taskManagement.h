#ifndef _TASK_MANAGEMENT
#define _TASK_MANAGEMENT

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "positioning/positionAlg.h"
#include "macros/indexing.h"
#include "macros/macroFunctions.h"
#include "api.h"

using namespace std;

extern PositionAlg position;
extern Indexing indexer;
extern pros::Task indexController;

#endif
