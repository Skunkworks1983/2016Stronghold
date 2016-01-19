#ifndef Drivebase_H
#define Drivebase_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Drivebase: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	Talon *leftMotor1, *leftMotor2, *leftMotor3, *rightMotor1, *rightMotor2, *rightMotor3;
public:
	Drivebase();
	~Drivebase();
	void InitDefaultCommand();
	void setLeftSpeed(double speed);
	void setRightSpeed(double speed);
};

#endif
