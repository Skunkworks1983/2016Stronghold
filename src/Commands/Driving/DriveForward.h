#ifndef DriveForward_H
#define DriveForward_H

#include <CommandBase.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <cstdbool>

class MotorManager;
class SensorManager;

class DriveForward: public CommandBase
{
private:
	float 			distance; 			//In inches (or the same units as wheel diameter)
	float 			speed;				//0-1 (decimal as percentage of full motor power)
	float 			initialYaw;			//Initial yaw at the start of the command
	float			initialPosition;	//Initial encoder position at start of command
	SensorManager * sensorManager;
	MotorManager * 	motorManager;
	float			errorOffset;		//Current enc position - initial enc position

	float			WHEEL_DIAMETER; //When we know, put it in a static variable somewhere else
	float			ENCODER_TICKS_PER_REVOLUTION; //When we know, put it in a static variable somewhere else
	//Todo: Check if ahrsDead and ignore all orient calls if it is
public:
	DriveForward(float distance, float speed); //distance to drive, speed at which to drive, whether or not to orient after drive is complete
	virtual 		~DriveForward();
	void 			Initialize();
	void 			Execute();
	bool 			IsFinished();
	void 			End();
	void 			Interrupted();
};

#endif
