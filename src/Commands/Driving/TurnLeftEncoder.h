#ifndef SRC_COMMANDS_TURNLEFTENCODER_H_
#define SRC_COMMANDS_TURNLEFTENCODER_H_

#include <CommandBase.h>
#include <cstdbool>

class TurnLeftEncoder: public CommandBase
{
private:
	double degrees;
	double initial;
public:
	TurnLeftEncoder(double degrees); //number of degrees to turn, speed at which to turn
	virtual ~TurnLeftEncoder();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};


#endif /* SRC_COMMANDS_TURNDEGREE_H_ */
