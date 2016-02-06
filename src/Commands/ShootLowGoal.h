/*
 * ShootLowGoal.h
 *
 *  Created on: Jan 30, 2016
 *      Author: s-4032218
 */
#include <Subsystems/Collector.h>
#include <Subsystems/SensorManager.h>
#include <CommandBase.h>
#ifndef SRC_COMMANDS_SHOOTLOWGOAL_H_
#define SRC_COMMANDS_SHOOTLOWGOAL_H_



class ShootLowGoal {
private:
	enum EShootState {
		SHOOT_STATE_AIMING,
		SHOOT_STATE_FIRING,
		SHOOT_STATE_RESETTING,
		SHOOT_STATE_FINISHED


	};
	float rollerSpeed;
	bool kickerActivated;
	int collectorRotatorSetpoint = 0; //unless that 0 isn't the automatic for collecting the ball
	int collectorRotatorPosition;
	SensorManager * sensorManager;
	Collector * collector;
	clock_t shootTime;
	EShootState shootState;
	const float SHOOTER_SPEED_TOLERANCE = 5;
	void ExecuteAiming();
	void ExecuteFiring();
	void ExecuteResetting();
public:
	ShootLowGoal();
	virtual ~ShootLowGoal();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif /* SRC_COMMANDS_ShootLowGoal_H_ */
