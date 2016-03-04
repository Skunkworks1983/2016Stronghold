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
	double error = 0.0;
	double outputspeed = 0.0;
	float speedTranslate = 0.0;
	float distance = 0.0;
	double initialPosition = 0.0;
public:
	RotateTowardCameraTarget(float speedTranslate = 0, float distance = 0);
	virtual ~RotateTowardCameraTarget();
	void Initialize();
	void Execute();bool IsFinished();
	void Interrupted();
	void End();
	void PIDWrite(float output);
};

#endif
