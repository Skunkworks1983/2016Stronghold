/*
 * .cpp
 *
 *  Created on: Jan 30, 2016
 *      Author: s-4032218
 */
/*
 * Problems with this program:
 * Need the actual numbers for the rotator position (numbers for collectorDegreeSetpoint

 */
#include <Commands/ShootHighGoal.h>

ShootHighGoal::ShootHighGoal() {
	// TODO Auto-generated constructor stub
this->speed = speed;
this->collectorDegreeSetpoint = collectorDegreeSetpoint;
this->collectorDegreePosition = collectorDegreePosition;
this->kickerActivated = kickerActivated;
}

ShootHighGoal::~ShootHighGoal() {
	// TODO Auto-generated destructor stub
}

void ShootHighGoal::Initialize()
{
	speed = 1;
	SensorManager * sensorManager = SensorManager::getSensorManager();
	Collector * collector = CommandBase::collector;
	sensorManager->GetEncoderPosition(COLLECTOR_ROTATOR_MOTOR_1_PORT);
	sensorManager->GetEncoderPosition(COLLECTOR_ROTATOR_MOTOR_2_PORT);
	collector->setRotatorPosition(collectorDegreeSetpoint);
}

void ShootHighGoal::Execute()
{
	SensorManager * sensorManager = SensorManager::getSensorManager();
	MotorManager * MotorManager = MotorManager::getMotorManager();
	Collector * collector = CommandBase::collector;
	this->collectorDegreePosition = sensorManager->GetEncoderPosition(COLLECTOR_ROTATOR_MOTOR_1_PORT);

	if (((collectorDegreeSetpoint - collectorDegreePosition) < 5) && ((collectorDegreeSetpoint - collectorDegreePosition) > -5)){
		MotorManager->setSpeed(COLLECTOR_ROTATOR_MOTOR_1_PORT, 0);
		MotorManager->setSpeed(COLLECTOR_ROTATOR_MOTOR_2_PORT, 0);
		collector->setRoller(Collector::KBackward, speed);
		if (MotorManager->getSpeed(COLLECTOR_ROLLER_MOTOR_1_PORT) == speed){
			MotorManager->setSpeed(COLLECTOR_KICKER_MOTOR_PORT, 1);
				kickerActivated = true;
		}

	}

}

bool ShootHighGoal::IsFinished()
{
 if (kickerActivated = true){
 		return true;
 	 } else {
 			return false;
	}

}

void ShootHighGoal::End()
{
	Collector * collector = CommandBase::collector;
	collector->setRoller(Collector::KStop, 0);
	collector->setRotatorPosition(0);
}

void ShootHighGoal::Interrupted()
{
	End();
}
