#ifndef ActivateKicker_H
#define ActivateKicker_H

#include "../CommandBase.h"
#include "WPILib.h"
#include <Subsystems/Collector.h>
#include <Subsystems/SensorManager.h>
#include <Subsystems/MotorManager.h>

class ActivateKicker: public CommandBase
{
private:
//	SensorManager * sensorManager; //not being used for anything, but could be useful?
	MotorManager * motorManager;
	Collector * collector;
	clock_t kickTime;
	bool kickerActivated;
	bool kickerDone;
public:
	ActivateKicker();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

};

#endif
