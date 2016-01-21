#include <Subsystems/Collector.h>

//TODO: set position of collector
//TODO: set speed
//TODO: need motor for rotation
//TODO: need motor for spinning
Collector::Collector() :
Subsystem("Collector") {
	rotatorMotor1 = new Talon(COLLECTOR_ROTATOR_MOTOR_1);
}

Collector::~Collector(){

}

void Collector::InitDefaultCommand(){

}

void Collector::resetEncoder(){

}

void Collector::setRotatorPosition(){

}

void Collector::motorRollerOn(){

}

void Collector::motorRollerOff(){

}
