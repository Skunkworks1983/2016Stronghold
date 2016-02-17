#include <CANTalon.h>
#include <Subsystems/Shooter_Collector.h>

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
	motorManager->setSpeed(COLLECTOR_ROTATOR_MOTOR_1_PORT, rotatorSpeed);
	motorManager->setSpeed(COLLECTOR_ROTATOR_MOTOR_2_PORT, rotatorSpeed);
}

double Collector::getRotatorPosition() {
	return sensorManager->GetEncoderPosition(COLLECTOR_ROTATOR_MOTOR_1_PORT);
}

void Collector::setRollerSpeed(rollerDirection direction, float speed) {
	motorManager->enablePID(PID_ID_ROLLER,1);
	switch (direction) {
	case KForward:
		motorManager->setSpeed(COLLECTOR_ROLLER_MOTOR_1_PORT, speed);
		motorManager->setSpeed(COLLECTOR_ROLLER_MOTOR_2_PORT, speed);
		break;

	case KBackward:
		motorManager->setSpeed(COLLECTOR_ROLLER_MOTOR_1_PORT, -speed);
		motorManager->setSpeed(COLLECTOR_ROLLER_MOTOR_2_PORT, -speed);
		break;

	case KStop:
		motorManager->setSpeed(COLLECTOR_ROLLER_MOTOR_1_PORT, 0.0);
		motorManager->setSpeed(COLLECTOR_ROLLER_MOTOR_2_PORT, 0.0);
		break;
	}
}

void Collector::setKickerSpeed(double kickerSpeed) {
	motorManager->setSpeed(COLLECTOR_ROTATOR_MOTOR_1_PORT, kickerSpeed);

}

void Collector::activateKicker(bool active) {
	if (active == true) {

	}
}
float Collector::getRollerSpeed() {
//needs code!

	}
void Collector::setRotatorPosition(float position){

}
void Collector::activateCollector(bool active){

}
Shooter::Shooter():
		Subsystem("Shooter") {

	sensorManager = SensorManager::getSensorManager();
	motorManager = MotorManager::getMotorManager();
}
void Shooter::activateShooter(bool active) {
	//motorManager->enablePID();

}

float Shooter::getSpeed() {

}
