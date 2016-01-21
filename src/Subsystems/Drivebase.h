#ifndef Drivebase_H
#define Drivebase_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Drivebase: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	Drivebase();
	void InitDefaultCommand();
	void setLeftSpeed(double speed);
	void setRightSpeed(double speed);
	float getLightSensorValue();
};

#endif
