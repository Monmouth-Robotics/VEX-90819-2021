#ifndef _UTILITY
#define _UTILITY

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include <vector>

using namespace std;

double calcAngleDiff(double angle1, double angle2);
double averageHeadings(double angle1, double angle2);
double averageHeadings(double angle1, double angle2, double angle3);
double headingAverageBeta(double angle1, double angle2, double angle3);
double dot(vector<double> a, vector<double> b);
double convertToRPM(double value, double wheelDiameter);
double convertToRPM(int value, double wheelDiameter);
double convertToMeters(double value, double wheelDiameter);
double convertToMeters(int value, double wheelDiameter);

#endif
