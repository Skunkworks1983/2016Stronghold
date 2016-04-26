#ifndef SensorManager_H
#define SensorManager_H

#include <stddef.h>
#include <Services/Sensor.h>
#include <cstdbool>
#include <map>

#define GYRO_NOT_CONNECTED_VALUE -4200

class AHRS;
class CANTalon;
class Encoder;

#define AHRS_CYCLE_TIMEOUT 500

class SensorManager {
	friend class MotorManager;
private:
	unsigned count = 0;
	AHRS * ahrs = NULL;
	std::map<unsigned, Sensor*> sensors;
	SensorManager();
	~SensorManager();
	int counter;
	double absoluteHeading = 0;
	double lastYaw = 0.0;
	//Declare other sensor types later (Encoder, Vision, etc)

public:
	static SensorManager* getSensorManager();
	void initGyro();

	float getYaw();
	float getPitch();
	float getRoll();

	float GetAccelX();
	float GetAccelY();
	float GetAccelZ();

	float getRawX();
	float getRawY();
	float getRawZ();

	float getAngle();

	float getFakeYaw();

	bool isMoving();

	double GetEncoderPosition(int ID);
	double GetSpeed(int ID);
	void ZeroYaw();
	bool ahrsDead;
	double startupYaw = 0;
	Sensor *getSensor(unsigned ID);
	AHRS *getGyro();
};

#endif
