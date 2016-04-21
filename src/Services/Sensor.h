/*
 * Sensor.h
 *
 *  Created on: Mar 21, 2016
 *      Author: S-4020395
 */

#ifndef SRC_SERVICES_SENSOR_H_
#define SRC_SERVICES_SENSOR_H_

#include <PIDSource.h>
#include <stddef.h>
#include <cstdbool>

class AHRS;
class CANTalon;

class Sensor: public PIDSource {
protected:
	AHRS * ahrs = NULL;
	CANTalon *talon = NULL;
	PIDSource *src = NULL;
	float lowRange = 0;
	float highRange = 0;
	unsigned ID = 0;
	bool reversed = false;
public:
	Sensor(unsigned CANTalonEncoderPort, float lowRange, float highRange,
			unsigned ID, bool reversed = false);
	Sensor(CANTalon *canTalon, float lowRange, float highRange, unsigned ID,
			bool reversed = false);
	Sensor(PIDSource *src, float lowRange, float highRange, unsigned ID,
			bool reversed = false);
	Sensor(AHRS * ahrs, float lowRange, float highRange, unsigned ID, bool reversed = false);
	virtual ~Sensor();
	double PIDGet();
	float getLowRange();
	float getHighRange();
	void resetEncoder();
	double getSpeed();
};

class SpeedSensor : public Sensor{
public:
	SpeedSensor(unsigned CANTalonEncoderPort, float lowRange, float highRange,
			unsigned ID, bool reversed = false);
	double PIDGet();
};

#endif /* SRC_SERVICES_SENSOR_H_ */
