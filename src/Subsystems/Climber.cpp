#include "Climber.h"
#include <RobotMap.h>

Climber::Climber() :
		Subsystem("Climber")
{

}

Climber::~Climber(){

}


void Climber::InitDefaultCommand()
{

}


void Climber::setwinchSpeed(float winchSpeed){
	MotorManager* motorManager = MotorManager::getMotorManager();
	motorManager->setSpeed(CLIMBER_MOTOR_1_PORT, winchSpeed);
	motorManager->setSpeed(CLIMBER_MOTOR_2_PORT, winchSpeed);
	motorManager->setSpeed(CLIMBER_MOTOR_3_PORT, winchSpeed);
	motorManager->setSpeed(CLIMBER_MOTOR_4_PORT, winchSpeed);
}

float Climber::getwinchSpeed(){
	return 1.0f;
}

void Climber::setArmSpeed(float armSpeed){
	MotorManager*motorManager = MotorManager::getMotorManager();
	motorManager->setSpeed(ARM_MOTOR_PORT, armSpeed);

}

float Climber::getArmSpeed(){
	return 1.0f;	//TODO: change this
}

float Climber::getWinchEncoder(){
	SensorManager::getSensorManager()->GetEncoderPosition(CLIMBER_MOTOR_1_PORT);
	return SensorManager::getSensorManager()->GetEncoderPosition(CLIMBER_MOTOR_1_PORT);
}

float Climber::getArmEncoder(){
	SensorManager::getSensorManager()->GetEncoderPosition(ARM_MOTOR_PORT);
		return SensorManager::getSensorManager()->GetEncoderPosition(ARM_MOTOR_PORT);
}

