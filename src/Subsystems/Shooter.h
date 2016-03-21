#ifndef SHOOTER_H
#define SHOOTER_H

#include <Commands/Subsystem.h>
#include <stddef.h>
#include <cstdbool>

class ShooterMotor;

class MotorManager;
class SensorManager;

class DigitalInput;

class Shooter: public Subsystem {
private:
	float p = .0024;	//works = .0018
	float i = 0.0;		//works = 0.0
	float d = 0.008;	//works = 0.0

	MotorManager *motorManager;
	SensorManager *sensorManager;
	DigitalInput *frontLimitSwitch;
	DigitalInput *backLimitSwitch;
	DigitalInput *breakBeam;
	ShooterMotor *left;
	ShooterMotor *right;
	Command *lastCommand = NULL;

	bool upToSpeed = false;
public:
	enum rollerDirection {
		KForward, KBackward, KStop
	};

	Shooter();
	~Shooter();

	void InitDefaultCommand();

	void setPID(float p, float i, float d);
	ShooterMotor *getLeft();
	ShooterMotor *getRight();

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
