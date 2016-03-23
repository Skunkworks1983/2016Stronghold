/*
 * BangBangTurn.h
 *
 *  Created on: Mar 22, 2016
 *      Author: S-4020395
 */

#ifndef SRC_COMMANDS_DRIVING_BANGBANGTURN_H_
#define SRC_COMMANDS_DRIVING_BANGBANGTURN_H_

#include <CommandBase.h>
#include <stddef.h>
#include <cstdbool>

class SensorManager;

class BangBangTurn : public CommandBase{
private:
	double targetDegrees = 0.0;
	unsigned onCount = 0;
	double speed = .5;
	SensorManager *sensorManager = NULL;
public:
	BangBangTurn(const double degrees);
	virtual ~BangBangTurn();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif /* SRC_COMMANDS_DRIVING_BANGBANGTURN_H_ */
