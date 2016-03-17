#include <CANTalon.h>
#include <Commands/Command.h>
#include <RobotMap.h>
#include <Services/Logger.h>
#include <Services/MotorManager.h>
#include <Servo.h>
#include <Subsystems/Climber.h>
#include <Subsystems/Shooter.h>
#include <cstdio>

Climber::Climber() :
		Subsystem("Climber") {
	servo = new Servo(CLIMBER_SERVO_PORT);
	lastCommand = NULL;
}

Climber::~Climber() {

}

void Climber::InitDefaultCommand() {

}

void Climber::setServoAngle(float angle) {
	servo->SetAngle(angle);
}

float Climber::getServoAngle() {
	return servo->GetAngle();
}

void Climber::setServoSpeed(float speed) {
	servo->Set(speed);
}

void Climber::setWinchSpeed(float winchSpeed) {
	MotorManager* motorManager = MotorManager::getMotorManager();
	motorManager->setSpeed(CLIMBER_WINCH_MOTOR_1_PORT, winchSpeed);
	motorManager->setSpeed(CLIMBER_WINCH_MOTOR_2_PORT, winchSpeed);
	motorManager->setSpeed(CLIMBER_WINCH_MOTOR_3_PORT, winchSpeed);
	motorManager->setSpeed(CLIMBER_WINCH_MOTOR_4_PORT, winchSpeed);
}

void Climber::registerCommand(Command *cmd) {
	if (lastCommand == NULL) {
		LOG_INFO("lastCommand = cmd");
		lastCommand = cmd;
	} else {
		if (lastCommand->IsRunning()) {
			lastCommand->Cancel();
		}
		lastCommand = cmd;
		LOG_INFO("After");
	}
	LOG_INFO("Command %d registered", cmd != NULL ? cmd->GetID() : -420);
}

void Climber::deregisterCommand(Command *cmd) {
	LOG_INFO("Command %d DEREGISTERED", cmd != NULL ? cmd->GetID() : -420);
	if (lastCommand == cmd) {
		if (lastCommand != NULL) {
			if (lastCommand->IsRunning()) {
				lastCommand->Cancel();
			}
		}
	}
}


void Climber::setSetpoint(float position) {
	armMotor->SetSetpoint(position);
	armMotor->EnableControl();
}



void Climber::disablePID() {
	armMotor->Disable();
}
