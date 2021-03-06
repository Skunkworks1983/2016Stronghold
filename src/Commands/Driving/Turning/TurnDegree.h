/*
 * TurnDegree.h
 *
 *  Created on: Jan 19, 2016
 *      Author: S-4032218
 */

#ifndef SRC_COMMANDS_TURNDEGREE_H_
#define SRC_COMMANDS_TURNDEGREE_H_

#include <CommandBase.h>
#include <PIDOutput.h>
#include <PIDSource.h>
#include <cstdbool>

class MotorManager;
class PIDController;
class SensorManager;

#define ENCODER_TURN_RADIUS_RATIO 1.2 // this is a placeholder for the actual ratio

class TurnDegree: public CommandBase
{
private:
	float degree;
	//double speed; See cpp
	bool absolute = false;
	bool ahrsDead;
	MotorManager * motorManager = NULL;
	SensorManager * sensorManager = NULL;
	float initialYaw;
	unsigned onCount = 0;
public:
	TurnDegree(double degree, bool absolute = false); //number of degrees to turn, speed at which to turn
	virtual ~TurnDegree();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	double P;
	double I;
	double D;
};


#endif /* SRC_COMMANDS_TURNDEGREE_H_ */
