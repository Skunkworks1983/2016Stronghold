/*
 * TurnDegree.h
 *
 *  Created on: Jan 19, 2016
 *      Author: S-4032218
 */

#ifndef SRC_COMMANDS_TURNDEGREE_H_
#define SRC_COMMANDS_TURNDEGREE_H_
#include <Subsystems/Drivebase.h>
#include <CommandBase.h>

class TurnDegree: public CommandBase
{
private:
	double degree;
	double placeholder;
	double speed;
public:
	TurnDegree(double degree, double placeholder);
	void SetLeftSpeed (double speed);
	void SetRightSpeed (double speed);
	void SetSetPoint (double targetTicks);
	virtual ~TurnDegree();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

};





#endif /* SRC_COMMANDS_TURNDEGREE_H_ */
