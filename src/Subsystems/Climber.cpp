#include <RobotMap.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <Servo.h>
#include <Subsystems/Climber.h>

Climber::Climber() :
		Subsystem("Climber") {
	servo = new Servo(CLIMBER_SERVO_PORT);
}

Climber::~Climber() {

}

void Climber::InitDefaultCommand() {

}

void Climber::setServoAngle(float angle){
	servo->SetAngle(angle);
}

float Climber::getServoAngle(){
	return servo->GetAngle();
}

void Climber::setServoSpeed(float speed){
	servo->Set(speed);
	//servo->SetSpeed(speed);
}

void Climber::setWinchSpeed(float winchSpeed) {
	MotorManager* motorManager = MotorManager::getMotorManager();
	motorManager->setSpeed(CLIMBER_WINCH_MOTOR_1_PORT, winchSpeed);
	motorManager->setSpeed(CLIMBER_WINCH_MOTOR_2_PORT, winchSpeed);
	motorManager->setSpeed(CLIMBER_WINCH_MOTOR_3_PORT, winchSpeed);
	motorManager->setSpeed(CLIMBER_WINCH_MOTOR_4_PORT, winchSpeed);
}
