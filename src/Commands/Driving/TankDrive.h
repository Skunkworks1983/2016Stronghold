#ifndef TankDrive_H
#define TankDrive_H

#include <CommandBase.h>
#include <cstdbool>

class TankDrive: public CommandBase
{
public:
	TankDrive();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
