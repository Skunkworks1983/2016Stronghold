#ifndef ZeroGyro_H
#define ZeroGyro_H

#include <CommandBase.h>
#include <cstdbool>

class ZeroGyro: public CommandBase
{
public:
	ZeroGyro();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
