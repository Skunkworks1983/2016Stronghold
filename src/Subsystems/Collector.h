#pragma once

#include <Commands/Subsystem.h>
#include <cstdbool>

class MotorManager;
class SensorManager;
class DigitalInput;

class Collector: public Subsystem {
private:
	SensorManager * sensorManager = NULL;
	MotorManager * motorManager = NULL;
	bool isDown = false;
	DigitalInput *breakBeam = NULL;

	Command *lastCommand = NULL;
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

	void registerCommand(Command *cmd);
	void deregisterCommand(Command *cmd);

	float getRotatorDegrees();

	bool getBreakBeam();
};
