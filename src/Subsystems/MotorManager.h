#ifndef MOTOR_MANAGER_H
#define MOTOR_MANAGER_H

#include <Commands/Subsystem.h>
#include <RobotMap.h>
#include <vector>


class CANTalon;

class Encoder;

enum Priority {
	PRIORITY_FIRST,
	PRIORITY_DRIVEBASE = PRIORITY_FIRST,
	PRIORITY_PRIMARY_ACTUATORS,
	PRIORITY_SECONDARY_ACTUATORS,
	PRIORITY_ACCESSORIES,
	PRIORITYS
};

class Motor {
	friend class MotorManager;
private:

public:
	Motor(Priority prioArg, int portArg);
	~Motor();
	CANTalon * talon;
	float      speed;
	Priority   motorPriority;
	int    	   port;
	float C;
	void setC(Priority priority, float voltage );


};

class MotorManager: public Subsystem {
	friend class SensorManager;
	friend class Motor;
private:
	MotorManager();
	~MotorManager();
	MotorManager(const MotorManager &);
	CANTalon* Motors[MAX_MANAGED_MOTORS];
	Priority allowedPriority;

	std::vector<Motor> motors;

	CANTalon * addMotor(Priority priority, int Port);

protected:
	double GetPosition(int ID);
	double GetSpeed(int ID);

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	void InitDefaultCommand();
	void setPosition(int pid, float position);
	void setSpeed(int ID, float speed);
	float getSpeed(int ID);
	int setPIDValues(int ID, double P, double I, double D);
	void setPriority(Priority priorityARG);

	static MotorManager * getMotorManager();
	void setCForAll();
	void setSpeedForAll();
};

#endif
