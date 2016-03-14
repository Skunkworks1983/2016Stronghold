#ifndef SHOOTER_H
#define SHOOTER_H

#include <Commands/Subsystem.h>
#include <stddef.h>
#include <cstdbool>

class MotorManager;
class SensorManager;

class DigitalInput;

class Shooter: public Subsystem {
private:
	MotorManager *motorManager;
	SensorManager *sensorManager;
	DigitalInput *frontLimitSwitch;
	DigitalInput *backLimitSwitch;
	DigitalInput *breakBeam;

	Command *lastCommand = NULL;

	bool upToSpeed = false;
public:
	enum rollerDirection {
		KForward, KBackward, KStop
	};

	Shooter();
	~Shooter();

	void InitDefaultCommand();

	void setUpToSpeed(bool upToSpeed);bool isUpToSpeed();

	void registerCommand(Command *cmd);
	void deregisterCommand(Command *cmd);

	bool getFrontSensor();
	bool getBackSensor();
	bool getBreakBeam();

	void setRollerSpeed(rollerDirection direction, float speed);

	float getRotatorDegrees();
	double getRotatorPosition();
	void setRotatorSpeed(float rotatorSpeed);

	float getLeftShooterSpeed();
	float getRightShooterSpeed();
	float getShooterSpeed();

	void setShooterSpeed(float speed);
	void setRightShooterSpeed(float speedRight);
	void setLeftShooterSpeed(float speedRight);

	float getLeftShooterMotorPower();
	float getRightShooterMotorPower();
};

#endif
