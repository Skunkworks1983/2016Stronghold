#ifndef ArcTurn_H
#define ArcTurn_H

#include <CommandBase.h>
#include <stddef.h>
#include <cstdbool>

struct TurnData;

class SensorManager;

class ArcTurn: public CommandBase
{
private:
	double targetDegrees = 0.0;
	double targetInput = 0.0;
	double speed = 0.0;
	double originalSpeed = 0.0;
	double initialLeft = 0.0;
	double initialRight = 0.0;
	double initialYaw = 0.0;
	double percentTurn = 0.0;
	unsigned onCount = 0;
	bool absolute = false;
	SensorManager *sensorManager = NULL;
	MotorManager *motorManger = NULL;
public:
	ArcTurn(double targetDegrees, double speed, double percentTurn, bool absolute = false);
	ArcTurn(TurnData *d);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
