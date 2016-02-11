/*
 * ShootHighGoal.h
 *
 *  Created on: Jan 30, 2016
 *      Author: s-4032218
 */
#include <Subsystems/SensorManager.h>
#include <CommandBase.h>
#include <Subsystems/Shooter_Collector.h>
#include "CollectorMove.h"
#ifndef SRC_COMMANDS_SHOOTHIGHGOAL_H_
#define SRC_COMMANDS_SHOOTHIGHGOAL_H_

class ShootGoal :public Command{
private:
	enum EShootState {
		SHOOT_STATE_FIRING,
		SHOOT_STATE_RESETTING,
		SHOOT_STATE_FINISHED
	};
	float rollerSpeed;
	int collectorRotatorSetpoint;
	float collectorRotatorPosition;
	EShootState shootState;
	SensorManager * sensorManager;
	Collector * collector;
	Shooter * shooter;
	const float SHOOTER_AIM_TOLERANCE = 5;
	const float SHOOTER_SPEED_TOLERANCE = 5;
	clock_t shootTime;
	void ExecuteOff();
	void ExecuteAiming();
	void ExecuteFiring();
	void ExecuteResetting();
public:
	ShootGoal();
	virtual ~ShootGoal();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif /* SRC_COMMANDS_SHOOTHIGHGOAL_H_ */
