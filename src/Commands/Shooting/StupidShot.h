#ifndef StupidShot_H
#define StupidShot_H

#include <CommandBase.h>
#include <cstdbool>

class StupidShot: public CommandBase
{
private:
	double targetSpeed = 0;
	double targetPower = 1.0;
	double realSpeed = 0;
	float timeout = 0;
	bool alreadyUp = false;
public:
	StupidShot(double targetSpeed, float timeout = 0);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
