#ifndef MoveBackUntilRoll_H
#define MoveBackUntilRoll_H

#include <CommandBase.h>
#include <cstdbool>

class MoveBackUntilRoll: public CommandBase {
private:
	unsigned count = 0;
public:
	MoveBackUntilRoll();
	void Initialize();
	void Execute();bool IsFinished();
	void End();
	void Interrupted();
};

#endif
