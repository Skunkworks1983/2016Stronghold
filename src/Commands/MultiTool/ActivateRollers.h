#ifndef ActivateRollers_H
#define ActivateRollers_H

#include <CommandBase.h>
#include <Subsystems/Collector.h>
#include <cstdbool>
#include <ctime>

class MotorManager;
class SensorManager;

class ActivateRollers: public CommandBase
{
private:
	MotorManager * motorManager = NULL;
	SensorManager * sensorManager = NULL;
	clock_t rollerTime;
	float timeOut;
	Collector::rollerDirection dir;
public:
	ActivateRollers(Collector::rollerDirection dir, float timeOut = 0);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
