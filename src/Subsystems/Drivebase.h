#ifndef DRIVEBASE_H
#define DRIVEBASE_H

#include <Commands/Subsystem.h>

class MotorManager;

class Drivebase: public Subsystem
{
public:
	bool stopHold = false;
	bool holdAgainstTower = false;
	Drivebase();
	~Drivebase();
	void InitDefaultCommand();
	void resetEncoder();
	void setLeftSpeed(double speed);
	void setRightSpeed(double speed);
	float getLeftDistance();
	float getRightDistance();
};

#endif
