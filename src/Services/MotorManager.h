#ifndef MOTOR_MANAGER_H
#define MOTOR_MANAGER_H

#include <Services/Motor.h>
#include <Services/PIDWrapper.h>
#include <cstdbool>
#include <map>

class MotorGroup;

class CANTalon;
class PIDController;
class Encoder;
class StallProtection;
class Motor;

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

	unsigned count = 0;

	Priority allowedPriority;

	std::map<unsigned, Motor*> motors;
	std::map<unsigned, PIDWrapper*> pidControllerMap;

	void addMotor(Priority priority, int Port, float maxCurrent,
			ESubsystem subsystem, bool reverse = false);

protected:
	double GetPosition(unsigned ID);
	double GetSpeed(unsigned ID);
public:
	Motor *getMotor(unsigned ID);

	void initPIDS();

	void resetPID(unsigned ID);
	void setPosition(unsigned pidID, float position);
	void setSpeed(unsigned ID, float speed);
	void setSpeedForAll();

	void setCForAll();

	int setPIDValues(unsigned ID, double P, double I, double D);
	void setPriority(Priority priorityARG);

	void setPID(unsigned ID, double P, double I, double D);
	void createPID(MotorGroup * group, unsigned PIDSourceID, unsigned pidID,
			float P, float I, float D, float F, bool isSpeedMode, bool isContinuous = false);
	void setPIDF(unsigned pidID, float P, float I, float D, float F);
	void enablePID(unsigned pidID, float setPoint);
	void enablePID(unsigned pidID);
	void disablePID(unsigned pidID);bool isPIDEnabled(unsigned pidID);
	PIDWrapper *getPID(unsigned pidID);

	static MotorManager * getMotorManager();
};

#endif
