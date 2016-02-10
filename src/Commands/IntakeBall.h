/*
 * IntakeBall.h
 *
 *  Created on: Jan 30, 2016
 *      Author: s-4032218
 */
#include <Subsystems/Collector.h>
#include <Subsystems/SensorManager.h>
#include <CommandBase.h>
#include "CollectorMove.h"
#ifndef SRC_COMMANDS_INTAKEBALL_H_
#define SRC_COMMANDS_INTAKEBALL_H_



class IntakeBall :public Command {
private:
	enum EIntakeBallState {
		INTAKE_STATE_COLLECTING,
		INTAKE_STATE_RESETTING,
		INTAKE_STATE_FINISHED
	};
	EIntakeBallState intakeState;
	SensorManager * sensorManager;
	Collector * collector;
	float collectorRotatorPosition;
	float rollerSpeed = 1;
	clock_t collectTime;
	void ExecuteCollecting();
	void ExecuteResetting();
public:
	IntakeBall();
	virtual ~IntakeBall();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif /* SRC_COMMANDS_IntakeBall_H_ */
