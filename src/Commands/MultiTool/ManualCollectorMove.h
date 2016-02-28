#ifndef MANUAL_COLLECTOR_MOVE_H
#define MANUAL_COLLECTOR_MOVE_H

#include <CommandBase.h>
#include <cstdbool>

class MotorManager;
class SensorManager;

class ManualCollectorMove: public CommandBase
{
private:
	float speed;
	float timeout;
	MotorManager * motorManager;
	SensorManager * sensorManager;
public:
	ManualCollectorMove(float speed, float timeout = 0);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

};

#endif
