/*
 * .cpp
 *
 *  Created on: Jan 30, 2016
 *      Author: s-4032218
 */
/*
 * Problems with this program:
 * Need the actual numbers for the rotator position (numbers for collectorRotatorSetpoint

 */
#include <Commands/ShootHighGoal.h>

ShootHighGoal::ShootHighGoal() {
	// TODO Auto-generated constructor stub
this->rollerSpeed = rollerSpeed;
this->collectorRotatorSetpoint = collectorRotatorSetpoint;
this->collectorRotatorPosition = collectorRotatorPosition;
this->kickerActivated = kickerActivated;
this->shootState = shootState;
}

ShootHighGoal::~ShootHighGoal() {
	// TODO Auto-generated destructor stub
}

void ShootHighGoal::Initialize()
{
	shootState = SHOOT_STATE_AIMING;

}

void ShootHighGoal::Execute()
{
	SensorManager * sensorManager = SensorManager::getSensorManager();
	MotorManager * MotorManager = MotorManager::getMotorManager();
	Collector * collector = CommandBase::collector;
	this->collectorRotatorPosition = sensorManager->GetEncoderPosition(COLLECTOR_ROTATOR_MOTOR_1_PORT);


		}

void ShootHighGoal::ExecuteAiming() {
	SensorManager * sensorManager = SensorManager::getSensorManager();
	Collector * collector = CommandBase::collector;
	MotorManager * MotorManager = MotorManager::getMotorManager();
	sensorManager->GetEncoderPosition(COLLECTOR_ROTATOR_MOTOR_1_PORT);
	sensorManager->GetEncoderPosition(COLLECTOR_ROTATOR_MOTOR_2_PORT);
	collector->setRotatorPosition(collectorRotatorSetpoint);
	if (((collectorRotatorSetpoint - collectorRotatorPosition) < 5) && ((collectorRotatorSetpoint - collectorRotatorPosition) > -5)){
			MotorManager->setSpeed(COLLECTOR_ROTATOR_MOTOR_1_PORT, 0);
			MotorManager->setSpeed(COLLECTOR_ROTATOR_MOTOR_2_PORT, 0);
			shootState = SHOOT_STATE_FIRING;
	}

}
void ShootHighGoal::ExecuteFiring() {
	Collector * collector = CommandBase::collector;
	MotorManager * MotorManager = MotorManager::getMotorManager();
	collector->setRoller(Collector::KBackward, rollerSpeed);
	if (MotorManager->getSpeed(COLLECTOR_ROLLER_MOTOR_1_PORT) == rollerSpeed){
		MotorManager->setSpeed(COLLECTOR_KICKER_MOTOR_PORT, 1);
			kickerActivated = true;
			shootState = SHOOT_STATE_RESETTING;
	}
}
void ShootHighGoal::ExecuteResetting() {
	Collector * collector = CommandBase::collector;
	MotorManager * MotorManager = MotorManager::getMotorManager();
	collector->setRoller(Collector::KStop, 0);
	collector->setRotatorPosition(0);
	if (collectorRotatorPosition < 5 && collectorRotatorPosition > -5){
			MotorManager->setSpeed(COLLECTOR_ROTATOR_MOTOR_1_PORT, 0);
			MotorManager->setSpeed(COLLECTOR_ROTATOR_MOTOR_2_PORT, 0);
	}
}

bool ShootHighGoal::IsFinished()
{
 if (kickerActivated == true && (collectorRotatorPosition < 5 && collectorRotatorPosition > -5)){
 		return true;
 	 } else {
 			return false;
	}

}

void ShootHighGoal::End()
{

}

void ShootHighGoal::Interrupted()
{
	End();
}
