#ifndef PIDGyroTest_H
#define PIDGyroTest_H

#include <CommandBase.h>
#include <PIDOutput.h>
#include <PIDSource.h>
#include <cstdbool>

#include <Services/MotorManager.h>
#include <Services/SensorManager.h>

class MotorManager;
class PIDController;
class SensorManager;

class PIDGyroTest: public CommandBase, public PIDOutput, public PIDSource
{
private:
	int degreeTurnRight;
	MotorManager * motorManager = NULL;
	SensorManager * sensorManager = NULL;
	PIDController * pidController  = NULL;
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
