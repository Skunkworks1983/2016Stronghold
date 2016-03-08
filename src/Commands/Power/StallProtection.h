#ifndef StallProtection_H
#define StallProtection_H

#include "../../CommandBase.h"
#include "WPILib.h"
#include <Services/MotorManager.h>
#include <RobotMap.h>

class StallProtection: public CommandBase
{
private:
	MotorManager * motorManager = NULL;
public:
	StallProtection();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
