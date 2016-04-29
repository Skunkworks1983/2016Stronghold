#ifndef DriveForwardStraightAccurate_H
#define DriveForwardStraightAccurate_H

#include <CommandBase.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <cstdbool>

#define USE_GYRO_TURN 1
#define CONTINUOUS_TEST 1

class MotorManager;
class SensorManager;

class DriveForwardStraightAccurate: public CommandBase {
private:
	float distance = 0; 			//In inches
	float speed = 0;				//0-1
	float initialYaw = 0;			//Initial yaw at the start of the command
	float inputSpeed = 0;
	double timeout = 0;
	SensorManager * sensorManager = NULL;

	double initialLeft = 0;
	double initialRight = 0;

	bool absolute = false;

	unsigned withinCount = 0;
public:
	DriveForwardStraightAccurate(float distance, float speed, double timeout = 0, bool absolute = false);
	virtual ~DriveForwardStraightAccurate();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
