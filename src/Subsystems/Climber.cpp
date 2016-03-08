#include <CANTalon.h>
#include <Commands/Command.h>
#include <RobotMap.h>
#include <Services/Logger.h>
#include <Services/MotorManager.h>
#include <Servo.h>
#include <Subsystems/Climber.h>
#include <Subsystems/Collector.h>
#include <cstdio>

Climber::Climber() :
		Subsystem("Climber") {
	servo = new Servo(CLIMBER_SERVO_PORT);
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
		Logger::getLogger()->log("lastCommand = cmd", Debug);
		lastCommand = cmd;
	} else {
		if (lastCommand->IsRunning()) {
			lastCommand->Cancel();
		}
		lastCommand = cmd;
		Logger::getLogger()->log("After", Debug);
	}
	char str[1024];
	sprintf(str, "Command %d registered", cmd != NULL ? cmd->GetID() : -420);
	Logger::getLogger()->log(str, Debug);
}

void Climber::deregisterCommand(Command *cmd) {
	char str[1024];
	sprintf(str, "Command %d DEREGISTERED", cmd != NULL ? cmd->GetID() : -420);
	Logger::getLogger()->log(str, Debug);
	if (lastCommand == cmd) {
		if (lastCommand != NULL) {
			if (lastCommand->IsRunning()) {
				lastCommand->Cancel();
				//Scheduler::GetInstance()->Remove(lastCommand);
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
