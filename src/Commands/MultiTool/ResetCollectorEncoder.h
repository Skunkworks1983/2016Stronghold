#ifndef RESETCOLLECTORMOVE_H
#define RESETCOLLECTORENCODER_H

#include <CommandBase.h>
#include <cstdbool>

class SensorManager;

class ResetCollectorEncoder: public CommandBase
{
private:
	SensorManager * sensorManager = NULL;
public:
	ResetCollectorEncoder();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

};

#endif /* SRC_COMMANDS_TURNDEGREE_H_ */
