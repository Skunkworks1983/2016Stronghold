#ifndef SHOOTER_H
#define SHOOTER_H

#include <Commands/Subsystem.h>
#include <cstdbool>

class Shooter: public Subsystem {
private:
public:
	Shooter();
	~Shooter();
	void InitDefaultCommand();
	void activateShooter(bool active);
	void setShooterSpeed(float speed);
	float getSpeed();
};

#endif
