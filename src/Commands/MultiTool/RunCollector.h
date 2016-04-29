#ifndef ActivateRollers_H
#define ActivateRollers_H

#include <CommandBase.h>
#include <Subsystems/Shooter.h>
#include <cstdbool>
#include <ctime>

class MotorManager;
class SensorManager;

#define COLLECT_SPEED 1.0

class RunCollector: public CommandBase
{
private:
	Shooter::rollerDirection dir;
	float speed = 0;
	float timeOut = 0;
	bool already_on  =false;
public:
	RunCollector(Shooter::rollerDirection dir, float speed = COLLECT_SPEED, float timeOut = 0);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
