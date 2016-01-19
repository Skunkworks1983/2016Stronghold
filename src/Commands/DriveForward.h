#ifndef DriveForward_H
#define DriveForward_H

#include "../CommandBase.h"
#include "OI.h"
#include "WPILib.h"

class DriveForward: public CommandBase
{
private:
	double distance;
	double speed;
public:
	DriveForward(double, double);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
