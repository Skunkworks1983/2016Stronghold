#include <DigitalInput.h>
#include <RobotMap.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <Subsystems/Collector.h>

Collector::Collector() :
		Subsystem("Collector") {
	sensorManager = SensorManager::getSensorManager();
	motorManager = MotorManager::getMotorManager();
	breakBeam = new DigitalInput(COLLECTOR_BREAK_BEAM_PORT);
}

Collector::~Collector() {
	delete breakBeam;
}

void Collector::InitDefaultCommand() {

}

void Collector::resetEncoder() {
	// motorManager->resetRollerEncoder(0.0);
}

bool Collector::getBreakBeam() {
	return !breakBeam->Get();
}

void Collector::setRotatorSpeed(float rotatorSpeed) {
	motorManager->setSpeed(COLLECTOR_ROTATOR_MOTOR_LEFT_PORT, rotatorSpeed);
	motorManager->setSpeed(COLLECTOR_ROTATOR_MOTOR_RIGHT_PORT, rotatorSpeed);
}

double Collector::getRotatorPosition() {
	return sensorManager->getSensor(SENSOR_COLLECTOR_ROTATION_ENCODER_ID)->PIDGet();
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
	if (active) {

	}
}

float Collector::getRollerSpeed() {
//needs code!
	return 0.0;
}

void Collector::setRotatorPosition(float position) {

}

float Collector::getRotatorDegrees() {
	return SensorManager::getSensorManager()->getSensor(
	SENSOR_COLLECTOR_ROTATION_ENCODER_ID)->PIDGet()
			/ COLLECTOR_ROTATION_TICKS_PER_DEGREE;
}

void Collector::activateCollector(bool active) {

}

