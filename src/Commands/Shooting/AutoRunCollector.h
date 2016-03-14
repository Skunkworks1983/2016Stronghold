#pragma once

#include <CommandBase.h>
#include <Subsystems/Shooter.h>
#include <cstdbool>

class MotorManager;
class SensorManager;

#define COLLECT_SPEED 1.0

class AutoRunCollector: public CommandBase {
private:
	double timeout = 0;
	bool alreadyUp = false;
public:
	AutoRunCollector();
	void Initialize();
	void Execute();bool IsFinished();
	void End();
	void Interrupted();
};
