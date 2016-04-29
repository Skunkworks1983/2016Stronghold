#ifndef TurnOnLight_H
#define TurnOnLight_H

#include <CommandBase.h>
#include <cstdbool>

class TurnOnLight: public CommandBase {
private:
	bool turnOn = true;bool toggle = false;
	double timeout = 0;
public:
	TurnOnLight(bool turnOn, bool toggle, double timeout = 0);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
