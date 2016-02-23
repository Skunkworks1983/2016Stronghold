#pragma once

#include <Commands/Subsystem.h>
#include <cstdbool>

class MotorManager;
class SensorManager;

class Collector: public Subsystem {
private:
	SensorManager * sensorManager;
	MotorManager * motorManager;bool isDown = false;

public:
	enum rollerDirection {
		KForward, KBackward, KStop
	};
	bool pidStopped;
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
