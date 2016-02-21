#ifndef SensorManager_H
#define SensorManager_H


#include <PIDSource.h>
#include <cstdbool>
#include <map>

class AHRS;
class CANTalon;
class Encoder;

#define AHRS_CYCLE_TIMEOUT 10

class Sensor : public PIDSource{
private:
	CANTalon *talon;
	PIDSource *src;
	unsigned ID;
public:
	Sensor(unsigned CANTalonEncoderPort, unsigned ID);
	Sensor(CANTalon *canTalon, unsigned ID);
	Sensor(PIDSource *src, unsigned ID);
	virtual ~Sensor(){};
	double PIDGet();
};

class SensorManager
{
	friend class MotorManager;
private:
	AHRS * ahrs;
	std::map<unsigned,Sensor*> sensors;
	SensorManager();
	~SensorManager();
	//Declare other sensor types later (Encoder, Vision, etc)

public:
	static SensorManager* getSensorManager();
	void initGyro();
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
	Sensor *getSensor(unsigned ID);
};

#endif
