#ifndef SHOOTER_H
#define SHOOTER_H

#include <Commands/Subsystem.h>
#include <cstdbool>

class Shooter: public Subsystem {
private:
	DigitalInput *frontLimitSwitch;
	DigitalInput *backLimitSwitch;
	DigitalInput *breakBeam;
public:
	Shooter();
	~Shooter();
	bool getFrontSensor();
	bool getBackSensor();
	bool getBreakBeam();

	void InitDefaultCommand();
	float getLeftShooterSpeed();
	float getRightShooterSpeed();

	void setShooterSpeed(float speed);
	void setRightShooterSpeed(float speedRight);
	void setLeftShooterSpeed(float speedRight);
};

#endif
