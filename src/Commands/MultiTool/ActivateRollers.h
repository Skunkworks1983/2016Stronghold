#ifndef ActivateRollers_H
#define ActivateRollers_H

#include <CommandBase.h>
#include <cstdbool>
#include <ctime>
#include <TuningValues.h>
#include <RobotMap.h>

class MotorManager;
class SensorManager;

class ActivateRollers: public CommandBase
{
private:
	MotorManager * motorManager;
	SensorManager * sensorManager;
	clock_t rollerTime;
	float timeOut;
public:
	ActivateRollers(float timeOut);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
