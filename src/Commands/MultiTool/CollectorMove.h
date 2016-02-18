#ifndef CollectorMove_H
#define CollectorMove_H

/*#include "../CommandBase.h"
#include "WPILib.h"

class CollectorMove: public CommandBase
{
public:
	CollectorMove();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
*/
#include <CommandBase.h>
#include <PIDOutput.h>
#include <PIDSource.h>
#include <Subsystems/Collector.h>
#include <TuningValues.h>
#include <RobotMap.h>

class CollectorMove: public CommandBase
{
private:
	float target;
	MotorManager * motorManager;
	SensorManager * sensorManager;

public:
	CollectorMove(float target);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

};

#endif /* SRC_COMMANDS_TURNDEGREE_H_ */
