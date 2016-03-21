#pragma once

#include <CommandBase.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include "RobotMap.h"

class BangBangControl: public CommandBase {
private:
	double targetSpeed;
	double timeOut;
	double realSpeed;
	bool alreadyRamped = false;
	double leftSpeed;
	double rightSpeed;
public:
	BangBangControl(double desiredSpeed, double timeOut = 0);
	~BangBangControl();
	void Initialize();
	void Execute();
	bool IsFinished();
	void Interrupted();
	void End();
};
