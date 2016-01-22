#include <CANTalon.h>
#include <RobotMap.h>
#include <Subsystems/Collector.h>

//TODO: set position of collector
//TODO: set speed
Collector::Collector() :
Subsystem("Collector") {
	rotatorMotor1 = new CANTalon(COLLECTOR_ROTATOR_MOTOR_1_PORT);
	rollerMotor1 = new CANTalon(COLLECTOR_ROLLER_MOTOR_1_PORT);
}

Collector::~Collector(){
	delete rotatorMotor1;
	delete rollerMotor1;
}

void Collector::InitDefaultCommand(){

}

void Collector::resetEncoder(){
	rotatorMotor1->Reset();
	rollerMotor1->Reset();
}

void Collector::setRotatorPosition(){
	rotatorMotor1->SetPosition(1); //TODO: find actual value
}

void Collector::motorRollerOn(){
	rollerMotor1->Set(1.0);
}

void Collector::motorRollerOff(){
	rollerMotor1->Set(0.0);
}

void Collector::setRotatorPosition(float position){

}
