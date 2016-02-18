#ifndef ActivateRollers_H
#define ActivateRollers_H

#include <CommandBase.h>
#include <cstdbool>
#include <ctime>

class MotorManager;
class SensorManager;

class ActivateRollers: public CommandBase
{
private:
	MotorManager * motorManager;
	SensorManager * sensorManager;
	clock_t rollerTime;
public:
	ActivateRollers();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
