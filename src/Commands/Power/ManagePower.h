#ifndef MANAGE_POWER_H
#define MANAGE_POWER_H

#include <CommandBase.h>
#include <cstdbool>

class MotorManager;

class ManagePower: public CommandBase {
private:
	MotorManager * manager;
public:
	ManagePower();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
