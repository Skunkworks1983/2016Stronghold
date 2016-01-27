#include <CANTalon.h>
#include <Subsystems/Collector.h>

//TODO: set position of collector
//TODO: set speed
Collector::Collector() :
Subsystem("Collector") {
	motorManager = MotorManager::getMotorManager();

}

Collector::~Collector(){
//ailis wants motor manager gone
}

void Collector::InitDefaultCommand(){

}

void Collector::resetEncoder(){
	// motorManager->resetRollerEncoder(0.0);
}

void Collector::setMotorPosition(){
	motorManager->setPosition(5, 2);
}

void Collector::setRotatorPosition(float position){

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
