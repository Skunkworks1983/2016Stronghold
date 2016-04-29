#ifndef DriveStraightUntilLevel_H
#define DriveStraightUntilLevel_H

#include <CommandBase.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <cstdbool>

#define USE_GYRO_TURN 1
#define CONTINUOUS_TEST 1

class MotorManager;
class SensorManager;

class DriveStraightUntilLevel: public CommandBase {
private:
	float distance; 			//In inches
	float speed;				//0-1
	float initialYaw;			//Initial yaw at the start of the command
	float initialPitch;
	float initialPosition;	//Initial encoder position at start of command
	SensorManager * sensorManager = NULL;
	float error;		//Current enc position - initial enc position
	//Todo: Check if ahrsDead and ignore all orient calls if it is
	double initialLeft;
	double initialRight;
	void setDistance(float distance, float speed);
public:
	DriveStraightUntilLevel(float distance, float speed); //distance to drive (ENCODER TICKS), speed at which to drive, whether or not to orient after drive is complete
	virtual ~DriveStraightUntilLevel();
	void Initialize();
	void Execute();bool IsFinished();
	void End();
	void Interrupted();
};

#endif
