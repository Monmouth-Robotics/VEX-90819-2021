#include "init/displayInstances.h"

//Creates an instance of Display to make it accessible globally
Display display;

//Create a task to display robot's position and heading
pros::Task displayController(display.displayPosition, NULL, "Position Display");