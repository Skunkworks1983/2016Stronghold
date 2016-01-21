#ifndef LINEFOLLOW_H
#define LINEFOLLOW_H

#include "../CommandBase.h"
#include "OI.h"
#include "WPILib.h"

class LineFollow: public CommandBase, PIDSource, PIDOutput {
private:
	PIDController *pid;
	AnalogInput *lightsensor;

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
