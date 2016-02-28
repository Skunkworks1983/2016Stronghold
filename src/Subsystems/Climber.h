#ifndef Climber_H
#define Climber_H

#include <Commands/Subsystem.h>

class Servo;

class Climber: public Subsystem
{
private:
	Servo *servo;
public:
	Climber();
	~Climber();

	void setServoAngle(float angle);
	float getServoAngle();
	void setServoSpeed(float speed);
	void setWinchSpeed(float winchSpeed);
	void InitDefaultCommand();
};

#endif
