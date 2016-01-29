#ifndef DRIVEBASE_H
#define DRIVEBASE_H

#include <Subsystems/MotorManager.h>
#include "Commands/Subsystem.h"
#include "WPILib.h"

class Drivebase: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	MotorManager * motorManager;

public:
	Drivebase();
	~Drivebase();
	void InitDefaultCommand();
	void resetEncoder();
	void setLeftSpeed(double speed);
	void setRightSpeed(double speed);
	float getLeftDistance(); //Maybe to be removed? Check on later -Eli
	float getRightDistance();
};

#endif
