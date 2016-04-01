#ifndef StopArmPID_H
#define StopArmPID_H

#include <CommandBase.h>
#include <cstdbool>

class StopArmPID: public CommandBase
{
public:
	StopArmPID();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
