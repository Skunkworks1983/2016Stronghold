#ifndef SRC_COMMANDS_TURNLEFTENCODER_H_
#define SRC_COMMANDS_TURNLEFTENCODER_H_

#include <CommandBase.h>
#include <stddef.h>
#include <cstdbool>

class SensorManager;

class TurnLeftEncoder: public CommandBase
{
private:
	double degrees;
	double initialEncoderTick;
	double speed;
	SensorManager *sensorManager = NULL;
public:
	TurnLeftEncoder(double degrees, double speed = 0.5); //number of degrees to turn, speed at which to turn
	virtual ~TurnLeftEncoder();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};


#endif /* SRC_COMMANDS_TURNDEGREE_H_ */
