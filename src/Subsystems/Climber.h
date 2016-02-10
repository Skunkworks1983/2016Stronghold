#ifndef Climber_H
#define Climber_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "MotorManager.h"

class Climber: public Subsystem
{
private:

public:
	Climber();
	~Climber();

	void setwinchSpeed(float winchSpeed);
	float getwinchSpeed();
	void setArmSpeed(float armSpeed);
	float getArmSpeed();
	void InitDefaultCommand();
	float getWinchEncoder();
	float getArmEncoder();
};

#endif
