#ifndef SensorManager_H
#define SensorManager_H

#include <Commands/Subsystem.h>

#include "WPILib.h"
#include "../../navx-mxp/cpp/include/AHRS.h"

class AHRS;
class AnalogInput;

class SensorManager: public Subsystem
{
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


};

#endif
