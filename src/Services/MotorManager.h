#ifndef MOTOR_MANAGER_H
#define MOTOR_MANAGER_H

#include <PIDController.h>
#include <PIDOutput.h>
#include <cstdbool>
#include <map>
#include <vector>

class CANTalon;
class PIDController;
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
	unsigned    	   port;
	float C;
	void setC(Priority priority, float voltage );
};

class MotorGroup: public PIDOutput {
private:
	std::vector<Motor*> motorList;
public:
	MotorGroup(std::vector<Motor*> motorgroup);
	virtual ~MotorGroup();
	void PIDWrite(float output);
};

class MotorManager {
	friend class SensorManager;
	friend class Motor;
private:
	MotorManager();
	~MotorManager();
	MotorManager(const MotorManager &);

	void initClimber();
	void initDriveBase();
	void initShooter();
	void initCollector();

	Priority allowedPriority;

	std::map<unsigned, Motor*> motors;
	std::map<unsigned, PIDController*> pidControllerMap;

	void addMotor(Priority priority, int Port);

protected:
	double GetPosition(unsigned ID);
	double GetSpeed(unsigned ID);
public:
	Motor *getMotor(unsigned ID);

	void setPosition(unsigned pidID, float position);
	void setSpeed(unsigned ID, float speed);
	void setSpeedForAll();

	void setCForAll();

	int setPIDValues(unsigned ID, double P, double I, double D);
	void setPriority(Priority priorityARG);

	void setPID(unsigned ID, double P, double I, double D);
	void createPID(MotorGroup * group, unsigned PIDSourceID, unsigned pidID, float P, float I, float D, float F, bool isSpeedMode);
	void setPIDF(unsigned pidID, float P, float I, float D, float F);
	void enablePID(unsigned pidID, float setPoint);
	void disablePID(unsigned pidID);

	static MotorManager * getMotorManager();
};

#endif
