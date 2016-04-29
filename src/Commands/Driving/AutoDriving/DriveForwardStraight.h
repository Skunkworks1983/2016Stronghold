#ifndef DriveForwardStraight_H
#define DriveForwardStraight_H

#include <CommandBase.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <cstdbool>

#define USE_GYRO_TURN 1
#define CONTINUOUS_TEST 1

class MotorManager;
class SensorManager;

class DriveForwardStraight: public CommandBase
{
private:
	float 			distance; 			//In inches
	float 			speed;				//0-1
	float 			initialYaw;			//Initial yaw at the start of the command
	float			initialPosition;	//Initial encoder position at start of command
	double timeout = 0;
	bool absolute = false;
	SensorManager * sensorManager = NULL;
	float			error = 0.0;		//Current enc position - initial enc position
	//Todo: Check if ahrsDead and ignore all orient calls if it is
	double initialLeft = 0;
	double initialRight = 0;
public:
	DriveForwardStraight(float distance, float speed, double timeout = 0, bool absolute =false); //distance to drive (ENCODER TICKS), speed at which to drive, whether or not to orient after drive is complete

	virtual 		~DriveForwardStraight();
	void 			Initialize();
	void 			Execute();
	bool 			IsFinished();
	void 			End();
	void 			Interrupted();
};

#endif
