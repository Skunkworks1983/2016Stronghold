#ifndef SpinUpShooter_H
#define SpinUpShooter_H

#include <CommandBase.h>
#include <cstdbool>

class MotorManager;
class SensorManager;

class SpinUpShooter: public CommandBase {

private:
	MotorManager * motorManager = NULL;
	SensorManager * sensorManager = NULL;
	float timeOut;
	float speed;

public:
	SpinUpShooter(float timeOut, float speed);
	void Initialize();
	void Execute();bool IsFinished();
	void End();
	void Interrupted();

};

#endif
