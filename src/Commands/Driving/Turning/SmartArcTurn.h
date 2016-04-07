#ifndef SmartArcTurn_H
#define SmartArcTurn_H

#include <CommandBase.h>
#include <stddef.h>
#include <cstdbool>

struct TurnData;

class SensorManager;

class SmartArcTurn: public CommandBase {
private:
	double targetDegrees = 0.0;
	double speed = 0.0;
	double initialLeft = 0.0;
	double initialRight = 0.0;
	double initialYaw = 0.0;
	double radius = 0.0;
	unsigned onCount = 0;
	SensorManager *sensorManager = NULL;
	MotorManager *motorManger = NULL;
public:
	SmartArcTurn(double targetDegrees, double speed, double radius);
	SmartArcTurn(TurnData *d);
	void Initialize();
	void Execute();bool IsFinished();
	void End();
	void Interrupted();
};

#endif
