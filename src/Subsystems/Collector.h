#ifndef COLLECTOR_H
#define COLLECTOR_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Collector: public Subsystem
{
private:
	Talon *rotatorMotor1, *rollerMotor1;
public:
	Collector();
	~Collector();
	void InitDefaultCommand();
	void setLeftSpeed(double speed);
	void setRightSpeed(double speed);
	void resetEncoder();
	void setRotatorPosition();
	void motorRollerOn();
	void motorRollerOff();
};

#endif
