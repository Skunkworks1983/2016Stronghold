#ifndef SpinUpShooter_H
#define SpinUpShooter_H

#include "../CommandBase.h"
#include "WPILib.h"
#include "Subsystems/MotorManager.h"
#include "OI.h"
#include "Subsystems/SensorManager.h"
#include "Subsystems/SensorManager.h"

class SpinUpShooter: public CommandBase
{

private:
	OI            * oi;
	MotorManager  * motorManager;
	SensorManager * sensorManager;


public:
	SpinUpShooter();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	float speed;


};

#endif
