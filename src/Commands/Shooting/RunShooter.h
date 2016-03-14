#pragma once

#include <CommandBase.h>
#include <cstdbool>

class RunShooter : public CommandBase{
private:
	double speed;
	double timeout;
	double realSpeed;
public:
	RunShooter(double speed, double timoeut = -1);
	~RunShooter();
	void Initialize();
	void Execute();
	bool IsFinished();
	void Interrupted();
	void End();
};
