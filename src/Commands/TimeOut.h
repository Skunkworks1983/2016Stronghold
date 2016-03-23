#ifndef TimeOut_H
#define TimeOut_H

#include "../CommandBase.h"
#include "WPILib.h"

class TimeOut: public CommandBase
{
private:
	float timeout = 0.0;
public:
	TimeOut(float timeout);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
