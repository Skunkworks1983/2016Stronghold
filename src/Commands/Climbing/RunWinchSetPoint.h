/*
 * RunWinch.h
 *
 *  Created on: Feb 21, 2016
 *      Author: S-4020395
 */

#ifndef SRC_COMMANDS_CLIMBING_RUNWINCHTOSETPOINT_H_
#define SRC_COMMANDS_CLIMBING_RUNWINCHTOSETPOINT_H_

#include <CommandBase.h>

class RunWinchToSetPoint: public CommandBase {
private:
	float setPoint, speed;
public:
	RunWinchToSetPoint(float setPoint, float speed);
	~RunWinchToSetPoint();
	void Initialize();
	void Execute();bool IsFinished();
	void Interrupted();
	void End();
};

#endif /* SRC_COMMANDS_CLIMBING_RUNWINCH_H_ */
