#ifndef MotorManager_H
#define MotorManager_H

#include "IMotor.h"

class MotorManager: public Subsystem
{
private:
	MotorManager();
	~MotorManager();
	MotorManager(const MotorManager &);
	IMotor * leftMotor1;
	IMotor * leftMotor2;
	IMotor * leftMotor3;
	IMotor * rightMotor1;
	IMotor * rightMotor2;
	IMotor * rightMotor3;
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	void InitDefaultCommand();
	void setLeftSpeed(double speed);
	void setRightSpeed(double speed);
	static MotorManager * getMotorManager();
};

#endif
