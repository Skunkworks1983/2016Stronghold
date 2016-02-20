#ifndef SpinUpShooter_H
#define SpinUpShooter_H

#include <CommandBase.h>
#include <cstdbool>

class MotorManager;
class SensorManager;

class SpinUpShooter: public CommandBase
{

private:
	OI            * oi;
	MotorManager  * motorManager;
	SensorManager * sensorManager;
	float timeOut;
	float speed;

public:
	SpinUpShooter(float timeOut, float speed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();


};

#endif
