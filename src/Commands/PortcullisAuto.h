/*
 * PortcullisAuto.h
 *
 *  Created on: Jan 27, 2016
 *      Author: s-2507264
 */

#ifndef SRC_PORTCULLISAUTO_H_
#define SRC_PORTCULLISAUTO_H_
#include <Subsystems/Drivebase.h>
#include <CommandBase.h>
#include <Subsystems/Collector.h>
#define EPSILON .0005f

class PortcullisAuto: public CommandBase{
private:
	float speed;
	float distance;
	float turnup;
	float dt; //distant traveled
	float turn;
	bool firststop;
public:
	PortcullisAuto(float speed, float distance, float turnup);
	void Initialize();
	~PortcullisAuto();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

};





#endif /* SRC_PORTCULLISAUTO_H_ */
