#ifndef RampToSpeed_H
#define RampToSpeed_H

#include <CommandBase.h>
#include <cstdbool>

class RampToSpeed: public CommandBase {
private:
	double realSpeed = 0.0;
	double targetSpeed = 0.0;
public:
	RampToSpeed(double targetSpeed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
