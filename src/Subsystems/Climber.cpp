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


void Climber::setWinchSpeed(float winchSpeed){
	MotorManager* motorManager = MotorManager::getMotorManager();
	motorManager->setSpeed(CLIMBER_WINCH_MOTOR_1_PORT, winchSpeed);
	motorManager->setSpeed(CLIMBER_WINCH_MOTOR_2_PORT, winchSpeed);
	motorManager->setSpeed(CLIMBER_WINCH_MOTOR_3_PORT, winchSpeed);
	motorManager->setSpeed(CLIMBER_WINCH_MOTOR_4_PORT, winchSpeed);
}

float Climber::getWinchSpeed(){
	return SensorManager::getSensorManager()->GetSpeed(CLIMBER_WINCH_MOTOR_1_PORT);
}

void Climber::setArmSpeed(float armSpeed){
	MotorManager*motorManager = MotorManager::getMotorManager();
	motorManager->setSpeed(CLIMBER_ARM_MOTOR_PORT, armSpeed);
}

float Climber::getArmSpeed(){
		return SensorManager::getSensorManager()->GetSpeed(CLIMBER_ARM_MOTOR_PORT);
}

float Climber::getWinchPos(){
	return SensorManager::getSensorManager()->GetEncoderPosition(CLIMBER_WINCH_MOTOR_1_PORT);
}

float Climber::getArmPos(){
	return SensorManager::getSensorManager()->GetEncoderPosition(CLIMBER_ARM_MOTOR_PORT);
}

