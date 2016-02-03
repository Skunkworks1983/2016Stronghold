#ifndef MotorManager_H
#define MotorManager_H
#include "SensorManager.h"
#include <Commands/Subsystem.h>
#include <RobotMap.h>

class CANTalon;
class Encoder;

class MotorManager: public Subsystem
{
private:
	MotorManager();
	~MotorManager();
	MotorManager(const MotorManager &);
	CANTalon* Motors[MAX_MANAGED_MOTORS];
protected:
	double GetPosition(int ID);

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	void InitDefaultCommand();
	void setPosition(int pid, float position);
	void setSpeed(int ID, float speed);
	float getSpeed(int ID);
	int setPIDValues(int ID, double P, double I, double D);
	void resetEncoder();
	static MotorManager * getMotorManager();
	friend SensorManager;

};

#endif
