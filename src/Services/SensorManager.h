#ifndef SensorManager_H
#define SensorManager_H

#include <PIDSource.h>
#include <cstdbool>
#include <map>

class AHRS;
class CANTalon;
class Encoder;

#define AHRS_CYCLE_TIMEOUT 10

class Sensor: public PIDSource {
private:
	AHRS * ahrs = NULL;
	CANTalon *talon = NULL;
	PIDSource *src = NULL;
	unsigned ID;
	float lowRange;
	float highRange;
	bool reversed;
public:
	Sensor(unsigned CANTalonEncoderPort, float lowRange, float highRange,
			unsigned ID, bool reversed = false);
	Sensor(CANTalon *canTalon, float lowRange, float highRange, unsigned ID,
			bool reversed = false);
	Sensor(PIDSource *src, float lowRange, float highRange, unsigned ID,
			bool reversed = false);
	Sensor(AHRS * ahrs, float lowRange, float highRange, unsigned ID, bool reversed = false);
	double PIDGet();
	float getLowRange();
	float getHighRange();
	int getAbsolutePosition();
	void resetEncoder();
};

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
	double GetSpeed(int ID);bool ahrsDead;
	double initialYaw;
	Sensor *getSensor(unsigned ID);
};

#endif
