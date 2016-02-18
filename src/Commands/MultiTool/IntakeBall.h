#pragma once

#include <Services/SensorManager.h>
#include <CommandBase.h>
#include <Subsystems/Collector.h>
#include "CollectorMove.h"

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

