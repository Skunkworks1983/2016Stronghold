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
	unsigned c = 0;
	bool autonomous = false;
	uint64_t startingTime = 0.0;
	double tolerance = 0.0;
public:
	AutoRunCollector(double tolerance, bool autonomous = false);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};
