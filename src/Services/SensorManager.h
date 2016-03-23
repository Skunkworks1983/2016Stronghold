#ifndef SensorManager_H
#define SensorManager_H

#include <stddef.h>
#include <Services/Sensor.h>
#include <cstdbool>
#include <map>

class AHRS;
class CANTalon;
class Encoder;

#define AHRS_CYCLE_TIMEOUT 100

class SensorManager {
	friend class MotorManager;
private:
	unsigned count = 0;
	AHRS * ahrs = NULL;
	std::map<unsigned, Sensor*> sensors;
	SensorManager();
	~SensorManager();
	int counter;
	//Declare other sensor types later (Encoder, Vision, etc)

public:
	static SensorManager* getSensorManager();
	void initGyro();
	float GetLightSensorVoltage();
	float getYaw();
	float getPitch();
	float getRoll();
	float GetAccelX();
	float GetAccelY();
	float GetAccelZ();
	double GetEncoderPosition(int ID);
	double GetSpeed(int ID);
	void ZeroYaw();
	bool ahrsDead;
	double startupYaw = 0;
	Sensor *getSensor(unsigned ID);
	AHRS *getGyro();
};

#endif
