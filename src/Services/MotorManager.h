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
class StallProtection;

enum Priority {
	PRIORITY_FIRST,
	PRIORITY_DRIVEBASE = PRIORITY_FIRST,
	PRIORITY_PRIMARY_ACTUATORS,
	PRIORITY_SECONDARY_ACTUATORS,
	PRIORITY_ACCESSORIES,
	PRIORITYS
};

enum ESubsystem {
	DRIVEBASE,
	WINCH,
	ARM,
	COLLECTOR_ROTATOR,
	ROLLER,
	SHOOTER
};

class Motor {
	friend class MotorManager;
private:
	bool reversed;
public:
	Motor(Priority prioArg, int portArg, float maxCurrent, ESubsystem parentSubsystem, bool reversed);
	~Motor();
	ESubsystem parentSubsystem;
	CANTalon * talon;
	float speed;
	float maxCurrent;
	long long int overCurrentStartTime;
	long long int stoppedStartTime;
	Priority motorPriority;
	unsigned port;
	float C;
	void setC(Priority priority, float voltage );
	bool isReversed();
};

class MotorGroup: public PIDOutput {
private:
	std::vector<Motor*> motorList;
public:
	MotorGroup(std::vector<Motor*> motorgroup);
	virtual ~MotorGroup();
	void PIDWrite(float output);
	int getPID(Motor motor);
};

class MotorManager {
	friend class SensorManager;
	friend class StallProtection;
	friend class Motor;
private:
	MotorManager();
	~MotorManager();
	MotorManager(const MotorManager &);

	void initClimber();
	void initDriveBase();
	void initShooter();
	void initCollector();
	void initArm();

	Priority allowedPriority;

	std::map<unsigned, Motor*> motors;
	std::map<unsigned, PIDController*> pidControllerMap;

	void addMotor(Priority priority, int Port, float maxCurrent, ESubsystem subsystem, bool reverse = false);

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
	void enablePID(unsigned pidID);
	void disablePID(unsigned pidID);
	bool isPIDEnabled(unsigned pidID);

	static MotorManager * getMotorManager();
};

#endif
