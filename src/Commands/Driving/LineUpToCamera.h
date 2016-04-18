#ifndef LineUpToCamera_H
#define LineUpToCamera_H

#include <CommandBase.h>
#include <cstdbool>

class LineUpToCamera: public CommandBase
{
public:
	LineUpToCamera();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
