#ifndef MOVETOWARDCAMERA
#define MOVETOWARDCAMERA

#include <CommandBase.h>
#include <PIDController.h>
#include <PIDOutput.h>
#include <PIDSource.h>
#include <cstdbool>

class RotateTowardCameraTarget: public CommandBase, public PIDOutput {
private:
	PIDController *controller = NULL;
	double error;
	double outputspeed;
public:
	RotateTowardCameraTarget();
	virtual ~RotateTowardCameraTarget();
	void Initialize();
	void Execute();bool IsFinished();
	void Interrupted();
	void End();
	void PIDWrite(float output);
};

#endif
