#include <RobotMap.h>
#include <Subsystems/Collector.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>

//TODO: set position of collector
//TODO: set speed
Collector::Collector() :
		Subsystem("Collector") {
	sensorManager = SensorManager::getSensorManager();
	motorManager = MotorManager::getMotorManager();

}

Collector::~Collector() {

}

void Collector::InitDefaultCommand() {

}

void Collector::resetEncoder() {
	// motorManager->resetRollerEncoder(0.0);
}

void Collector::setRotatorSpeed(float rotatorSpeed) {
	motorManager->setSpeed(COLLECTOR_ROTATOR_MOTOR_LEFT_PORT, rotatorSpeed);
	motorManager->setSpeed(COLLECTOR_ROTATOR_MOTOR_RIGHT_PORT, rotatorSpeed);
}

double Collector::getRotatorPosition() {
	return sensorManager->GetEncoderPosition(COLLECTOR_ROTATOR_MOTOR_LEFT_PORT);
}

void Collector::setRollerSpeed(rollerDirection direction, float speed) {
	switch (direction) {
	case KForward:
		motorManager->setSpeed(COLLECTOR_ROLLER_MOTOR_1_PORT, speed);
		break;

	case KBackward:
		motorManager->setSpeed(COLLECTOR_ROLLER_MOTOR_1_PORT, -speed);
		break;

	case KStop:
		motorManager->setSpeed(COLLECTOR_ROLLER_MOTOR_1_PORT, 0.0);
		break;
	}
}

void Collector::setKickerSpeed(double kickerSpeed) {
	motorManager->setSpeed(COLLECTOR_ROTATOR_MOTOR_LEFT_PORT, kickerSpeed);

}

void Collector::activateKicker(bool active) {
	if (active == true) {

	}
}
float Collector::getRollerSpeed() {
//needs code!
	return 0.0;
	}
void Collector::setRotatorPosition(float position){

}

void Collector::activateCollector(bool active){

}

