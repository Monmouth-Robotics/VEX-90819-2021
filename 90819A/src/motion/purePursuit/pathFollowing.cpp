#include "motion/purePursuit/pathFollowing.h"

/*
Creates function that takes in current x, y, and theta and lookahead point x, y, theta, and returns proper error. 
Function rotates the lookahead position about the robot origin.
*/

vector<double> getErrors(vector<double> currentPosition, vector<double>lookAheadPosition)
{
  vector<double> adjustedError;
  
  //calculates new x coordinate
  double rotatedX = cos(currentPosition[2]) * (lookAheadPosition[0] - currentPosition[0]) - sin(currentPosition[2]) * (lookAheadPosition[1] - currentPosition[1]) + currentPosition[0];
  //calculates new y coordinate
  double rotatedY = sin(currentPosition[2]) * (lookAheadPosition[0] - currentPosition[0]) + cos(currentPosition[2]) * (lookAheadPosition[1] - currentPosition[1]) + currentPosition[1];
  
  //calculates x error
  double xError = rotatedX - currentPosition[0];
  //calculates y error
  double yError = rotatedY - currentPosition[0];
  //calculates angle error
  double angleError = calcAngleDiff(currentPosition[2], lookAheadPosition[2]);

  //creates error vector
  adjustedError[0] = xError;
  adjustedError[1] = yError;
  adjustedError[2] = angleError;


  return adjustedError;
}