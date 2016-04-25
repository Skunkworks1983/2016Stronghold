#ifndef PIDTurn_H
#define PIDTurn_H

#include <CommandBase.h>
#include <cstdbool>

struct TurnData;

class PIDTurn: public CommandBase
{
private:
	double target = 0;
	bool absolute = false;
	double input = 0;
	unsigned correctCount = 0;
	bool first = false;
	double timeout = 0;
public:
	PIDTurn(double target, bool absolute, double timeout = 0);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
