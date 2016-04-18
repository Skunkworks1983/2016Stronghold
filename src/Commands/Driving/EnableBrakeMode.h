#ifndef EnableBrakeMode_H
#define EnableBrakeMode_H

#include <CommandBase.h>
#include <cstdbool>

class EnableBrakeMode: public CommandBase
{
private:
	bool brake = true;
	double timeout = 0.0;
public:
	EnableBrakeMode(bool brake, double timeout);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
