/*
 * PortcullisAuto.cpp
 *
 *  Created on: Jan 27, 2016
 *      Author: s-2507264
 */

#include <Commands/Defences/PortcullisAuto.h>
#include <Commands/MultiTool/CollectorMove.h>
#include <Subsystems/Collector.h>
#include <Subsystems/Drivebase.h>
#include <cmath>

PortcullisAuto::PortcullisAuto(float speed, float distance, float turnup){
	Requires(drivebase);
	Requires(collector);
	this->speed = speed;
	this->distance = distance;
	this->turnup = turnup;
	this->dt = 0;
	this->turn = turn;
	this->firststop = false;

}

void PortcullisAuto::Initialize(){
	drivebase->resetEncoder();
	drivebase->setLeftSpeed(speed);
	drivebase->setRightSpeed(speed);
	drivebase->getLeftDistance();


}
PortcullisAuto::~PortcullisAuto(){

}

void PortcullisAuto::Execute(){
	this->dt = drivebase->getRightDistance();
	if (fabs(distance-dt) <= EPSILON && firststop==false) {
		this->firststop = true;
		drivebase->setRightSpeed(0);
		drivebase->setLeftSpeed(0);
	}
//	CollectorMove(turnup);
	if ((turnup - turn) < EPSILON){

	}
	this->dt = drivebase->getRightDistance();
	drivebase->setLeftSpeed(speed);
	drivebase->setRightSpeed(speed);
	}


bool PortcullisAuto::IsFinished(){
	if ((2*distance-dt) <= EPSILON && (turnup-turn) <= EPSILON){
		return true;
	}
	else {
		return false;
	}
}

void PortcullisAuto::End(){
	drivebase->setLeftSpeed(0);
	drivebase->setRightSpeed(0);
	CollectorMove(0);
}

void PortcullisAuto::Interrupted(){
	End();
}
