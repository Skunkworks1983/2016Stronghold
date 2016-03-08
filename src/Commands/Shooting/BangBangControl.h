#pragma once

#include <CommandBase.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include "RobotMap.h"


class BangBangControl : public CommandBase{
private:
	double desiredSpeed;
	float currentSpeed;
	double timeActivated;
	MotorManager * motorManager = NULL;
	SensorManager * sensorManager = NULL;
public:
	BangBangControl(double desiredSpeed, double timeActivated);
	~BangBangControl();
	void Initialize();
	void Execute();
	bool IsFinished();
	void Interrupted();
	void End();
};
