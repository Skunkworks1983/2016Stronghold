#ifndef ShooterMove_H
#define ShooterMove_H

#include <CommandBase.h>
#include <PIDOutput.h>
#include <PIDSource.h>
#include <Subsystems/Shooter.h>
#include <TuningValues.h>
#include <RobotMap.h>

enum ShooterPosition {
	cTOP, cCollect, c45, c60
};

class RotateShooter: public CommandBase {
private:
	float target;
	MotorManager * motorManager = NULL;
	SensorManager * sensorManager = NULL;
	int test;
	bool noreset = false;
	float timeout = 0;
public:
	RotateShooter(ShooterPosition pos, bool noreset = false, float fimeout = 0);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

};

#endif /* SRC_COMMANDS_TURNDEGREE_H_ */
