#ifndef PIDGyroTest_H
#define PIDGyroTest_H

#include "CommandBase.h"
#include "WPILib.h"
#include "../../Subsystems/MotorManager.h"
#include "../../Subsystems/SensorManager.h"
#include "PIDController.h"
#include "RobotMap.h"

class PIDGyroTest: public CommandBase, public PIDOutput, public PIDSource
{
private:
	int degreeTurnRight;
	MotorManager * motorManager;
	SensorManager * sensorManager;
	PIDController * pidController;
	float yawTurnTo;
public:
	PIDGyroTest();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	double PIDGet();
	void PIDWrite(float output);
};

#endif
