#ifndef SmartTurn_H
#define SmartTurn_H

#include <CommandBase.h>
#include <stddef.h>
#include <cstdbool>

#define DEGREE_TOLERANCE 2.0

class SensorManager;

enum INPUT_LEVEL {
	GYRO, ENCODER, TIME
};

class SmartTurn: public CommandBase {
private:
	double target = 0.0;bool absolute = false;
	double initialLeft = 0.0;
	double initialRight = 0.0;
	double initialSpeed = .6;
	unsigned count = 0;
	unsigned onCount = 0;

	bool alreadyRan = false;

	INPUT_LEVEL current_level = GYRO;
	SensorManager *sensorManager = NULL;

	double P = 1. / 140.0;
	double I = 1.0 / 3000.0;
	double D = 1.0 / 20.0;
public:
	SmartTurn(double targetDegrees, bool absolute = false);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
