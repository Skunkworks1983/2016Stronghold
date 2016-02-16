#ifndef COLLECTOR_H
#define COLLECTOR_H

#include <Subsystems/SensorManager.h>
#include <Subsystems/MotorManager.h>
#include <CommandBase.h>
class Shooter: public Subsystem{

private:
	SensorManager * sensorManager;
	MotorManager *motorManager;

	//this is the best code ever - Tucker Bowlin 2016
public:
	Shooter();
	void activateShooter(bool active);
	void setShooterSpeed(float speed);
	float getSpeed();


};
class Collector: public Subsystem {
private:
	SensorManager * sensorManager;
	MotorManager * motorManager;

public:
	enum rollerDirection {
		KForward, KBackward, KStop
	};

	Collector();
	~Collector();
	void InitDefaultCommand();
	void resetEncoder();
	void setRotatorSpeed(float rotatorSpeed); //now with code!
	void setRotatorPosition(float position);
	double getRotatorPosition(); //now with code!
	void setRollerSpeed(rollerDirection direction, float speed);
	float getRollerSpeed();
	void setKickerSpeed(double kickerSpeed);
	void activateKicker(bool active); //put actual things into this!
	void activateShooter(bool active); //parameterize this and also put actual things into this!
	void activateCollector(bool active); //put actual things into this!

};

#endif
