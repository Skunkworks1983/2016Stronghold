#include <CANTalon.h>
#include <Subsystems/Collector.h>

//TODO: set position of collector
//TODO: set speed
Collector::Collector() :
Subsystem("Collector") {
	sensorManager = SensorManager::getSensorManager();
	motorManager = MotorManager::getMotorManager();
	P = 0.0075;
	I = 0;
	D = 0;
	pidController = new PIDController(P, I, D, this, this);


}

Collector::~Collector(){
//ailis wants motor manager gone
}

void Collector::InitDefaultCommand(){

}

void Collector::resetEncoder(){
	// motorManager->resetRollerEncoder(0.0);
}

void Collector::setRotatorSpeed(float rotatorSpeed) {
	motorManager->setSpeed(COLLECTOR_ROTATOR_MOTOR_1_PORT, rotatorSpeed);
	motorManager->setSpeed(COLLECTOR_ROTATOR_MOTOR_2_PORT, rotatorSpeed);
}


double Collector::getRotatorPosition() {
	return sensorManager->GetEncoderPosition(COLLECTOR_ROTATOR_MOTOR_1_PORT);
}

void Collector::setRoller(rollerDirection direction, float speed){
	switch(direction){
	case KForward:
		motorManager->setSpeed(COLLECTOR_ROLLER_MOTOR_1_PORT, speed);
		motorManager->setSpeed(COLLECTOR_ROLLER_MOTOR_2_PORT, speed);
		break;

	case KBackward:
		motorManager->setSpeed(COLLECTOR_ROLLER_MOTOR_1_PORT,-speed);
		motorManager->setSpeed(COLLECTOR_ROLLER_MOTOR_2_PORT,-speed);
		break;

	case KStop:
		motorManager->setSpeed(COLLECTOR_ROLLER_MOTOR_1_PORT, 0.0);
		motorManager->setSpeed(COLLECTOR_ROLLER_MOTOR_2_PORT, 0.0);
		break;
	}
}

void Collector::PIDWrite(float rotatorSpeed) {
	motorManager->setSpeed(COLLECTOR_ROTATOR_MOTOR_1_PORT, rotatorSpeed); // ???

}

double Collector::PIDGet() {

return sensorManager->GetEncoderPosition(COLLECTOR_ROTATOR_MOTOR_1_PORT); //is this right??? No idea
}

void Collector::setKickerSpeed(double kickerSpeed) {
	motorManager->setSpeed(COLLECTOR_ROTATOR_MOTOR_1_PORT, kickerSpeed);

}

void Collector::activateKicker(bool active) {
	if (active == true) {

	}
}

void Collector::activateShooter(bool active) {

}

void Collector::activateCollector(bool active) {

}

float Collector::getRollerSpeed() {
//needs code!
	}





