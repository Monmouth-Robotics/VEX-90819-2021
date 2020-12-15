#include "init/taskManagement.h"

PositionAlg position;

//Create a task to keep track of the robot's position and heading
pros::Task positionController(position.calcPosition, NULL, "Position Tracker");

//Creates instance of indexer class to use indexing functions
Indexing indexer;

//Create a task to automate the motion of the stacks when balls enter
pros::Task indexController(indexer.indexingTask, NULL, "Ball Tracker");