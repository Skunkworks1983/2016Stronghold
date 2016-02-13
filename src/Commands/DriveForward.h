#ifndef DriveForward_H
#define DriveForward_H
#include <Subsystems/SensorManager.h>
#include <Subsystems/MotorManager.h>
#include <CommandBase.h>
#include <cstdbool>
#include "Subsystems/Drivebase.h"

class DriveForward: public CommandBase
{
private:
	float 			distance; 			//In inches
	float 			speed;				//0-1
	float 			initialYaw;			//Initial yaw at the start of the command
	float			initialPosition;	//Initial encoder position at start of command
	SensorManager * sensorManager;
	MotorManager * 	motorManager;
	float			errorOffset;		//Current enc position - initial enc position
	//Todo: Check if ahrsDead and ignore all orient calls if it is
public:
	DriveForward(float distance, float speed); //distance to drive (ENCODER TICKS), speed at which to drive, whether or not to orient after drive is complete
	virtual 		~DriveForward();
	void 			Initialize();
	void 			Execute();
	bool 			IsFinished();
	void 			End();
	void 			Interrupted();
};

#endif
