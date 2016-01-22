#ifndef COLLECTOR_H
#define COLLECTOR_H

#include <Commands/Subsystem.h>

class CANTalon;

class Collector: public Subsystem
{
private:
	CANTalon *rotatorMotor1, *rollerMotor1;
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
	void setRotatorPosition(float position);
};

#endif
