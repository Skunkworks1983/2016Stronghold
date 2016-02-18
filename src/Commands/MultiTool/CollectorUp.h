#ifndef CollectorUp_H
#define CollectorUp_H

#include <CommandBase.h>
#include <cstdbool>

#include "Services/MotorManager.h"
#include "Services/SensorManager.h"

#define EPSILON .0005f

class CollectorUp: public CommandBase
{
private:
	float currentTurnPos;
	double turnPos;
	float speed;
public:
	CollectorUp(float currentTurnPos, double turnPos, float speed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
