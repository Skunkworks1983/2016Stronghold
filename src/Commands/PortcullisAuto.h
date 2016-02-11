/*
 * PortcullisAuto.h
 *
 *  Created on: Jan 27, 2016
 *      Author: s-2507264
 */

#ifndef SRC_PORTCULLISAUTO_H_
#define SRC_PORTCULLISAUTO_H_
#include <Subsystems/Drivebase.h>
#include <Commandbase.h>
#include <Subsystems/Shooter_Collector.h>
#include <Commands/CollectorMove.h>
#define EPSILON .0005f

class Portcullis: public CommandBase{
private:
	float speed;
	float distance;
	float turnup;
	float dt; //distant traveled
	float turn;
	bool firststop;
public:
	Portcullis(float speed, float distance, float turnup);
	void Initialize();
	~Portcullis();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

};





#endif /* SRC_PORTCULLISAUTO_H_ */
