#ifndef ReadShooterPIDValues_H
#define ReadShooterPIDValues_H

#include <CommandBase.h>
#include <cstdbool>

class ReadShooterPIDValues: public CommandBase
{
public:
	ReadShooterPIDValues();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
