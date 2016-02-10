#ifndef DriveForward_H
#define DriveForward_H
#include <Subsystems/SensorManager.h>
#include <CommandBase.h>
#include <cstdbool>
#include "Subsystems/Drivebase.h"

class DriveForward: public CommandBase
{
private:
	float 			distance;
	float 			speed;
	float 			initialYaw;
	float 			newYaw;
	bool 			startedCorrection;
	SensorManager * sensorManager;
public:
	DriveForward(float distance, float speed, bool orient); //distance to drive, speed at which to drive, whether or not to orient after drive is complete
	virtual 		~DriveForward();
	void 			Initialize();
	void 			Execute();
	bool 			IsFinished();
	void 			End();
	void 			Interrupted();
};

#endif