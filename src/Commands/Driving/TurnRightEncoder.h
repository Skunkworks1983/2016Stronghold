#ifndef SRC_COMMANDS_TURNRIGHTENCODER_H
#define SRC_COMMANDS_TURNRIGHTENCODER_H

#include <CommandBase.h>
#include <cstdbool>

class TurnRightEncoder: public CommandBase
{
private:
	double degrees;
	double initial;
public:
	TurnRightEncoder(double degrees); //number of degrees to turn, speed at which to turn
	virtual ~TurnRightEncoder();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};


#endif /* SRC_COMMANDS_TURNDEGREE_H_ */
