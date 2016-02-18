#pragma once

#include <CommandBase.h>

class LowBar: public CommandBase {
private:

public:
	LowBar();
	~LowBar();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};
