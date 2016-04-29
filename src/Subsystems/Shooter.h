#ifndef SHOOTER_H
#define SHOOTER_H

#include <Commands/Subsystem.h>
#include <stddef.h>
#include <TuningValues.h>
#include <cstdbool>

class DigitalOutput;
class ShooterMotor;
class MotorManager;
class SensorManager;
class DigitalInput;

class Shooter: public Subsystem {
private:
	float p = SHOOTER_LEFT_P;	//works = .0018
	float i = SHOOTER_LEFT_I;		//works = 0.0
	float d = SHOOTER_LEFT_D;	//works = 0.0

	bool lightState = false;

	//working values
//	float p = .003;
//	float i = 0.0;
//	float d = 0.012;

	MotorManager *motorManager = NULL;
	SensorManager *sensorManager = NULL;
	ShooterMotor *left = NULL;
	ShooterMotor *right = NULL;
	Command *lastCommand = NULL;

	DigitalOutput *light = NULL;

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

	bool getLightState();
	void turnOnLight(bool state);
};

#endif
