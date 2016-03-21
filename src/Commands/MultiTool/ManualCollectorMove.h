#ifndef MANUAL_COLLECTOR_MOVE_H
#define MANUAL_COLLECTOR_MOVE_H

#include <CommandBase.h>
#include <cstdbool>

class MotorManager;
class SensorManager;

class ManualRotateShooter: public CommandBase
{
private:
	float speed;
	float timeout;
public:
	ManualRotateShooter(float speed, float timeout = 0);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

};

#endif
