#include <Commands/MultiTool/ManualCollectorMove.h>
#include <RobotMap.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <cstdbool>

//TODO: Find the conversion ratio for encoder ticks to degrees
ManualCollectorMove::ManualCollectorMove(float speed, float timeout) :
		speed(speed), timeout(timeout) {

	sensorManager = SensorManager::getSensorManager();
	motorManager = MotorManager::getMotorManager();
}

void ManualCollectorMove::Initialize() {
	if(timeout != 0){
		SetTimeout(timeout);
	}
	motorManager->setSpeed(COLLECTOR_ROTATOR_MOTOR_LEFT_PORT, speed);
	motorManager->setSpeed(COLLECTOR_ROTATOR_MOTOR_RIGHT_PORT, speed);

}

void ManualCollectorMove::Execute() {

}

bool ManualCollectorMove::IsFinished() {
	return false;
}

void ManualCollectorMove::End() {
	motorManager->setSpeed(COLLECTOR_ROTATOR_MOTOR_LEFT_PORT, speed);
	motorManager->setSpeed(COLLECTOR_ROTATOR_MOTOR_RIGHT_PORT, speed);
}

void ManualCollectorMove::Interrupted() {
	End();
}
