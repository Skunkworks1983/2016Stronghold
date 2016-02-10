#ifndef LINEFOLLOW_H
#define LINEFOLLOW_H
#include "Subsystems/SensorManager.h"
#include "../CommandBase.h"
#include "OI.h"
#include "WPILib.h"

class LineFollow: public CommandBase, PIDSource, PIDOutput {
private:
	PIDController *pid;
	SensorManager * sensorManager;

public:
	LineFollow();
	~LineFollow();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	double PIDGet();
	void PIDWrite(double output);


};

#endif
