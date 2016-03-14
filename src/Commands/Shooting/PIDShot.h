#ifndef PIDShot_H
#define PIDShot_H

#include <CommandBase.h>
#include <cstdbool>

class ShooterMotor;

class PIDShot: public CommandBase {
private:
	ShooterMotor *left;
	ShooterMotor *right;
	unsigned c = 0;
	double leftSpeed;
	double rightSpeed;
public:
	PIDShot(double leftSpeed, double rightSpeed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
