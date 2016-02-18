#ifndef SensorManager_H
#define SensorManager_H


#include "Commands/Subsystem.h"
#include "WPILib.h"
#include <AHRS.h>

#define AHRS_CYCLE_TIMEOUT 10

class SensorManager: public Subsystem
{
	friend class MotorManager;
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	AHRS * ahrs;
	AnalogInput *lightSensor;


	SensorManager();
	~SensorManager();
	//Declare other sensor types later (Encoder, Vision, etc)
public:
	static SensorManager* getSensorManager();
	void InitDefaultCommand();
	float GetLightSensorVoltage();
	float getYaw();
	float getPitch();
	float getRoll();
	float  GetAccelX();
	float  GetAccelY();
	float  GetAccelZ();
	double GetEncoderPosition(int ID);
	double GetSpeed(int ID);
	bool ahrsDead;
	int counter;
};

#endif
