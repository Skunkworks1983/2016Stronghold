#ifndef DRIVEBASE_H
#define DRIVEBASE_H

#include <Commands/Subsystem.h>

class MotorManager;

class Drivebase: public Subsystem
{
private:
	bool holding = false;
public:
	Drivebase();
	~Drivebase();
	void InitDefaultCommand();
	void resetEncoder();
	void setLeftSpeed(double speed);
	void setRightSpeed(double speed);

	void setLeftSpeed(const double speed1, const double speed2, const double speed3);
	void setRightSpeed(const double speed1, const double speed2, const double speed3);
	float getLeftDistance();
	float getRightDistance();

	void setHold(bool state);
	bool isHolding();
};

#endif
