#ifndef ReadPIDValues_H
#define ReadPIDValues_H

#include <CommandBase.h>
#include <cstdbool>

class ReadPIDValues: public CommandBase
{
private:
	unsigned PIDId = -1;
public:
	ReadPIDValues(const unsigned PIDId);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
