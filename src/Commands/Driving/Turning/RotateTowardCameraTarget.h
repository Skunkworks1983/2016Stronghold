#ifndef MOVETOWARDCAMERA
#define MOVETOWARDCAMERA

#include <CommandBase.h>
#include <PIDOutput.h>
#include <stddef.h>
#include <cstdbool>
#include <WPILib.h>

class PIDController;

class RotateTowardCameraTarget: public CommandBase, public PIDOutput {
private:
	PIDController *controller = NULL;
	double error = 0.0;
	double outputspeed = 0.0;
	unsigned onTargetCount = 0;
	float timeout = 0.0;
	unsigned PIDWriteCounter = 0;
public:
	RotateTowardCameraTarget(float timeout = 0.0);
	virtual ~RotateTowardCameraTarget();
	void Initialize();
	void Execute();
	bool IsFinished();
	void Interrupted();
	void End();
	void PIDWrite(float output);
};

#endif
