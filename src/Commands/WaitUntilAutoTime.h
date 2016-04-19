#ifndef WaitUntilAutoTime_H
#define WaitUntilAutoTime_H

#include "../CommandBase.h"
#include "WPILib.h"

class WaitUntilAutoTime: public CommandBase
{
private:
	double secondsIntoAuto = 0;
public:
	WaitUntilAutoTime(double secondsIntoAuto);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
