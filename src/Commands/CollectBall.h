/*
 * CollectBall.h
 *
 *  Created on: Jan 30, 2016
 *      Author: s-4032218
 */
#include <Subsystems/Collector.h>
#include <Subsystems/SensorManager.h>
#include <CommandBase.h>
#ifndef SRC_COMMANDS_CollectBall_H_
#define SRC_COMMANDS_CollectBall_H_



class CollectBall {
private:
	enum ECollectBallState {
		COLLECT_STATE_AIMING,
		COLLECT_STATE_COLLECTING,
		COLLECT_STATE_RESETTING,
		COLLECT_STATE_FINISHED
	};
	ECollectBallState collectState;
	SensorManager * sensorManager;
	Collector * collector;
	float collectorRotatorPosition;
	float rollerSpeed = 1;
	clock_t collectTime;
	void ExecuteAiming();
	void ExecuteCollecting();
	void ExecuteResetting();
public:
	CollectBall();
	virtual ~CollectBall();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif /* SRC_COMMANDS_CollectBall_H_ */
