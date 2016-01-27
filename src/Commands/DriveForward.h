#ifndef DriveForward_H
#define DriveForward_H

#include <CommandBase.h>
#include "Subsystems/Drivebase.h"

class DriveForward: public CommandBase
{
private:
	float distance;
	float speed;
public:
	DriveForward(float, float);
	virtual ~DriveForward();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
