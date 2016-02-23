#ifndef MOVETOWARDCAMERA
#define MOVETOWARDCAMERA

#include <CommandBase.h>
#include <PIDController.h>
#include <PIDOutput.h>
#include <PIDSource.h>
#include <cstdbool>

class RotateTowardCameraTarget : public CommandBase, public PIDOutput, public PIDSource{
private:
	PIDController *controller;
	double error, outputspeed;
	unsigned invalidCount;
	bool lostTarget;
	int closeEnoughCount;
public:
	RotateTowardCameraTarget();
	virtual ~RotateTowardCameraTarget();
	void Initialize();
	void Execute();
	bool IsFinished();
	void Interrupted();
	void End();
	void PIDWrite(float output);
	double PIDGet();
};

#endif
