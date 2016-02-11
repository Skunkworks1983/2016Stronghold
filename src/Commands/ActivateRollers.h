#ifndef ActivateRollers_H
#define ActivateRollers_H

#include "../CommandBase.h"
#include "WPILib.h"
#include <Subsystems/Collector.h>
#include <PIDOutput.h>
#include <PIDSource.h>

class ActivateRollers: public CommandBase
{
private:
	MotorManager * motorManager;
	SensorManager * sensorManager;
	PIDController * pidController;
	double P;
	double I;
	double D;
	double PIDGet();
	void PIDWrite(float output);
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
