#ifndef SensorManager_H
#define SensorManager_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "AHRS.h"

class SensorManager: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	AHRS * ahrs;
	AnalogInput *lightSensor;
	//Declare other sensor types later (Encoder, Vision, etc)
public:
	SensorManager();
	void InitDefaultCommand();
	float GetLightSensorVoltage();
	float getYaw();
	float getPitch();
	float getRoll();
};

#endif
