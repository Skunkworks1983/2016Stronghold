#ifndef SpinUpShooter_H
#define SpinUpShooter_H

#include "../CommandBase.h"
#include "WPILib.h"
#include "Subsystems/MotorManager.h"
#include "OI.h"
#include "Subsystems/SensorManager.h"
#include "Subsystems/SensorManager.h"

class SpinUpShooter: public CommandBase, PIDSource, PIDOutput
{

private:
	OI            * oi;
	MotorManager  * motormanager;
	SensorManager * sensormanager;
	PIDController * pid;


public:
	SpinUpShooter();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	float P;
	float I;
	float D;
	float speed;
	double PIDGet();
	void PIDWrite(float output);

};

#endif
