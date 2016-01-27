#ifndef MotorManager_H
#define MotorManager_H

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
	Encoder* getEncoder(int ID);

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	void InitDefaultCommand();
	void setPosition(int pid, float position);
	void setSpeed(int ID, float speed);
	int setPIDValues(int ID, double P, double I, double D);

	static MotorManager * getMotorManager();
};

#endif
