#ifndef Climber_H
#define Climber_H

#include <Commands/Subsystem.h>

class CANTalon;

class Servo;

class Climber: public Subsystem {
private:
	Servo *servo = NULL;
	CANTalon *armMotor = NULL;
	Command *lastCommand = NULL;
public:
	Climber();
	~Climber();

	void registerCommand(Command *cmd);
	void deregisterCommand(Command *cmd);
	void setServoAngle(float angle);
	float getServoAngle();
	void setServoSpeed(float speed);
	void setWinchSpeed(float winchSpeed);
	void InitDefaultCommand();
	void setSetpoint(float position);
	void disablePID();
};

#endif
