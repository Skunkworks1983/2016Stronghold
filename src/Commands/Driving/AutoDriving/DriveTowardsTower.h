#ifndef DriveTowardsTower_H
#define DriveTowardsTower_H

#include <CommandBase.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <cstdbool>

class MotorManager;
class SensorManager;

class DriveTowardsTower: public CommandBase {
private:
	float speed = 0;				//0-1
	float inputSpeed = 0;
	double P = 0;
	double timeout = 0;
	SensorManager * sensorManager = NULL;
	double oldCamAngle = 0;
	double initialAngle = 0;
	double initialLeft = 0;
	double initialRight = 0;
public:
	DriveTowardsTower(float speed, double P, double timeout = 0);
	virtual ~DriveTowardsTower();
	void Initialize();
	void Execute();bool IsFinished();
	void End();
	void Interrupted();
};

#endif
