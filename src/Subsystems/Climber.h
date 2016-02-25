#ifndef Climber_H
#define Climber_H

#include <Commands/Subsystem.h>

class Climber: public Subsystem
{
private:

public:
	Climber();
	~Climber();

	void setWinchSpeed(float winchSpeed);
	float getWinchSpeed();
	void setArmSpeed(float armSpeed);
	float getArmSpeed();
	void InitDefaultCommand();
	float getWinchPos();
	float getArmPos();
};

#endif
