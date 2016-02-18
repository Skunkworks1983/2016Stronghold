#pragma once

#include <CommandBase.h>

class BangBangControl : public CommandBase{
private:
	double desiredSpeed;
public:
	BangBangControl(double desiredSpeed);
	~BangBangControl();
	void Initialize();
	void Execute();
	bool IsFinished();
	void Interrupted();
	void End();
};
