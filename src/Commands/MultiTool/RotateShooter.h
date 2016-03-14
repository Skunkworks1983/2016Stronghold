#ifndef ShooterMove_H
#define ShooterMove_H

#include <CommandBase.h>
#include <PIDOutput.h>
#include <PIDSource.h>
#include <Subsystems/Shooter.h>
#include <TuningValues.h>
#include <RobotMap.h>

enum ShooterPosition {
	cTOP, cCollect, c45
};

class RotateShooter: public CommandBase {
private:
	float target;
	MotorManager * motorManager = NULL;
	SensorManager * sensorManager = NULL;
	int test;
public:
	RotateShooter(ShooterPosition pos);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

};

#endif /* SRC_COMMANDS_TURNDEGREE_H_ */
