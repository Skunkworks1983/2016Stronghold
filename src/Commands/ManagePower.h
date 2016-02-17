#ifndef MANAGE_POWER_H
#define MANAGE_POWER_H

#include "WPILib.h"
#include <CommandBase.h>
#include <cstdbool>
#include <Services/MotorManager.h>

class MotorManager;

class ManagePower: public CommandBase {

private:


	MotorManager * manager;

public:
	ManagePower(MotorManager * manager);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
