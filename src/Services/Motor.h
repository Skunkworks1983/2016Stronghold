#ifndef SRC_SERVICES_MOTOR_H_
#define SRC_SERVICES_MOTOR_H_

#include <stddef.h>
#include <cstdbool>

class CANTalon;

enum Priority {
	PRIORITY_FIRST,
	PRIORITY_DRIVEBASE = PRIORITY_FIRST,
	PRIORITY_PRIMARY_ACTUATORS,
	PRIORITY_SECONDARY_ACTUATORS,
	PRIORITY_ACCESSORIES,
	PRIORITYS
};

enum ESubsystem {
	DRIVEBASE, WINCH, ARM, COLLECTOR_ROTATOR, ROLLER, SHOOTER
};

class Motor {
	friend class MotorManager;
private:
	bool reversed;
	bool brownoutProtect;
public:
	Motor(Priority prioArg, int portArg, float maxCurrent,
			ESubsystem parentSubsystem, bool brownoutProtect, bool reversed);
	~Motor();
	ESubsystem parentSubsystem;
	CANTalon * talon = NULL;
	float speed;
	float maxCurrent;
	long long int overCurrentStartTime;
	long long int stoppedStartTime;
	Priority motorPriority;
	unsigned port;
	float C;
	void setSpeed(float speed);
	void setC(Priority priority, float voltage);
	bool isReversed();
	bool isBrownoutProtect();
};

#endif /* SRC_SERVICES_MOTOR_H_ */
