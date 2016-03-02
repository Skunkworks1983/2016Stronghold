#ifndef ActivateKicker_H
#define ActivateKicker_H

#include <CommandBase.h>
#include <cstdbool>
#include <ctime>

class MotorManager;

class ActivateKicker: public CommandBase
{
private:
//	SensorManager * sensorManager; //not being used for anything, but could be useful?
	MotorManager * motorManager = NULL;
	Collector * collector = NULL;
	float timeOut;
public:
	ActivateKicker();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

};

#endif
