#ifndef Drivebase_H
#define Drivebase_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "./MotorManager.h"


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
	void setLeftSpeed(double);
	void setRightSpeed(double);
	float getLeftDistance(); //Maybe to be removed? Check on later -Eli
	float getRightDistance();
};

#endif
