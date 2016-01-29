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
#define ENCODER_TURN_RADIUS_RATIO 1.2 // this is a placeholder for the actual ratio

class TurnDegree: public CommandBase
{
private:
	double degree;
	double speed;
public:
	TurnDegree(double degree, double speed); //number of degrees to turn, speed at which to turn
	virtual ~TurnDegree();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};





#endif /* SRC_COMMANDS_TURNDEGREE_H_ */
