#ifndef ArcTurnToCamera_H
#define ArcTurnToCamera_H

#include <CommandBase.h>
#include <stddef.h>
#include <cstdbool>

class SensorManager;

class ArcTurnToCamera: public CommandBase
{
private:
	double targetDegrees = 0.0;
	double targetInput = 0.0;
	double speed = 0.0;
	double initialLeft = 0.0;
	double initialRight = 0.0;
	double initialYaw = 0.0;
	double percentTurn = 0.0;
	unsigned onCount = 0;
	double timeout = 0;

	bool invalidCamera = false;
	SensorManager *sensorManager = NULL;
	MotorManager *motorManger = NULL;
public:
	ArcTurnToCamera(double speed, double percentTurn, double timeout = 0);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
