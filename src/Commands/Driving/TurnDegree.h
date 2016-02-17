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

class TurnDegree: public CommandBase, public PIDOutput, public PIDSource
{
private:
	double degree;
	//double speed; See cpp
	bool ahrsDead;
	MotorManager * motorManager;
	SensorManager * sensorManager;
	PIDController * pidController;
public:
	TurnDegree(double degree); //number of degrees to turn, speed at which to turn
	virtual ~TurnDegree();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	double P;
	double I;
	double D;
	double PIDGet();
	void PIDWrite(float output);
};





#endif /* SRC_COMMANDS_TURNDEGREE_H_ */
