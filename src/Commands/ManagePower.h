#ifndef MANAGE_POWER_H
#define MANAGE_POWER_H

#include "WPILib.h"
#include <CommandBase.h>
#include <cstdbool>
#include <Subsystems/MotorManager.h>

class MotorManager;

class ManagePower: public CommandBase {
private:
	PowerDistributionPanel * powerPanel;

	MotorManager * manager;

public:
	ManagePower(MotorManager* manager);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
