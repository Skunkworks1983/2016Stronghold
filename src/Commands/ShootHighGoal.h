/*
 * ShootHighGoal.h
 *
 *  Created on: Jan 30, 2016
 *      Author: s-4032218
 */
#include <Subsystems/Collector.h>
#include <Subsystems/SensorManager.h>
#include <CommandBase.h>
#ifndef SRC_COMMANDS_SHOOTHIGHGOAL_H_
#define SRC_COMMANDS_SHOOTHIGHGOAL_H_

class ShootHighGoal {
private:
	float speed;
	int collectorDegreeSetpoint;
	int collectorDegreePosition;
	bool kickerActivated;
public:
	ShootHighGoal();
	virtual ~ShootHighGoal();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif /* SRC_COMMANDS_SHOOTHIGHGOAL_H_ */
