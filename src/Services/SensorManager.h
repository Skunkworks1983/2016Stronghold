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
	CANTalon *talon;
	PIDSource *src;
	unsigned ID;
	float lowRange, highRange;
public:
	Sensor(unsigned CANTalonEncoderPort, float lowRange, float highRange,
			unsigned ID);
	Sensor(CANTalon *canTalon, float lowRange, float highRange, unsigned ID);
	Sensor(PIDSource *src, float lowRange, float highRange, unsigned ID);
	virtual ~Sensor() {
	}
	;
	double PIDGet();
	float getLowRange();
	float getHighRange();
};

class SensorManager {
	friend class MotorManager;
private:
	unsigned count = 0;
	AHRS * ahrs;
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
	bool ahrsDead;
	double initialYaw;
	Sensor *getSensor(unsigned ID);
};

#endif
