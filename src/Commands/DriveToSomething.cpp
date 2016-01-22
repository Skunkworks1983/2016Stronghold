/*
 *  DriveToSomething.cpp
 *
 *  Created on: Jan 19, 2016
 *      Author: s-2507264
 */
#include<Subsystems/Drivebase.h>
#include<Commands/DriveToSomething.h>

DriveToSomething::DriveToSomething(float distance, int speed){

 }

void DriveToSomething::Initialize(){
	drivebase->setRightSpeed(speed);
	drivebase->setLeftSpeed(speed);
}

void DriveToSomething::Execute(){

}

bool DriveToSomething::IsFinished(){

}

void DriveToSomething::End(){

}

void DriveToSomething::Interrupted(){

}
