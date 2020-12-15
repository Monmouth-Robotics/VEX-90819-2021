#ifndef _PATH_FOLLOWING
#define _PATH_FOLLOWING
#include "api.h"
#include "positioning/positionAlg.h"
#include "macros/indexing.h"
#include "init/utility.h"
#include <vector>

using namespace std;

vector<double> getErrors(vector<double> currentPosition, vector<double>lookAheadPosition);

#endif
