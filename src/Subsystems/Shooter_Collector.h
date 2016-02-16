#ifndef COLLECTOR_H
#define COLLECTOR_H

#include <Subsystems/SensorManager.h>
#include <Subsystems/MotorManager.h>
#include <CommandBase.h>
class Shooter: public Subsystem{
	friend class Collector;
private:
	//this is the best code ever - Tucker Bowlin 2016
public:
	Shooter();
	void activateShooter();
	float getSpeed();


};
class Collector: public Subsystem, public PIDSource, public PIDOutput {
private:
	SensorManager * sensorManager;
	MotorManager *motorManager;
	PIDController * pidController;
public:
	enum rollerDirection {
		KForward, KBackward, KStop
	};

	Collector();
	~Collector();
	double P;
	double I;
	double D;
	double PIDGet();
	void PIDWrite(float output);
	void InitDefaultCommand();
	void resetEncoder();
	void setRotatorSpeed(float rotatorSpeed); //now with code!
	double getRotatorPosition(); //now with code!
	void setRoller(rollerDirection direction, float speed);
	float getRollerSpeed();
	void setKickerSpeed(double kickerSpeed);
	void activateKicker(bool active); //put actual things into this!
	void activateShooter(bool active); //parameterize this and also put actual things into this!
	void activateCollector(bool active); //put actual things into this!

};

#endif