#ifndef COLLECTOR_H
#define COLLECTOR_H

#include <Subsystems/MotorManager.h>
#include <CommandBase.h>

class Collector: public Subsystem {
private:
	MotorManager *motorManager;
public:
	enum rollerDirection {
		KForward, KBackward, KStop
	};

	Collector();
	~Collector();
	void InitDefaultCommand();
	void setLeftSpeed(double speed);
	void setRightSpeed(double speed);
	void resetEncoder();
	void setRotatorPosition(float position);
	void setRoller(rollerDirection direction, float speed);
	float getRollerSpeed();
	void activateKicker(bool active); //put actual things into this!
	void activateShooter(bool active); //parameterize this and also put actual things into this!
	void activateCollector(bool active); //put actual things into this!

};

#endif
