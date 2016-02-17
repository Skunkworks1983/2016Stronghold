#ifndef CollectorUp_H
#define CollectorUp_H

#include "../CommandBase.h"
#include "WPILib.h"
#include "Subsystems/Shooter_Collector.h"
#include "Subsystems/MotorManager.h"
#include "Subsystems/SensorManager.h"
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
