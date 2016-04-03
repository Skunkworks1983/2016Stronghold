#ifndef PIDShot_H
#define PIDShot_H

#include <CommandBase.h>
#include <cstdbool>

class ShooterMotor;

class PIDShot: public CommandBase {
private:
	unsigned c = 0;
	double leftSpeed;
	double rightSpeed;
	float timeout;
	float current_left_setpoint = 5;
	float current_right_setpoint = 5;
public:
	PIDShot(double leftSpeed, double rightSpeed, float timeout = 0.0);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
