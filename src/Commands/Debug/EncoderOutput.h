#ifndef EncoderOutput_H
#define EncoderOutput_H

#include "../../CommandBase.h"
#include "WPILib.h"
#include <Services/SensorManager.h>

class EncoderOutput: public CommandBase
{
private:
	SensorManager * sensorManager;
public:
	EncoderOutput();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
