#ifndef _INTAKE_CONTROLLER
#define _INTAKE_CONTROLLER

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "init/devices.h"
#include "init/taskManagement.h"

using namespace std;

namespace zoo {
	class IntakeController
	{
	public:
		IntakeController();
		void toggleIntakes(int speed);
		bool getIntakeStatus();
		static void deploy(void* ignore);
		static void stopIntakesAsync(void* ignore);
		static void stopIntakesAsyncOne(void* ignore);
	private:
		static bool intakeStatus;
	};
}

#endif