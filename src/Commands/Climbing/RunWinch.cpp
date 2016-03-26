#include <Commands/Climbing/RunWinch.h>
#include <RobotMap.h>
#include <Services/MotorManager.h>
#include <Subsystems/Climber.h>
#include <Subsystems/Drivebase.h>
#include <TuningValues.h>
#include <cstdbool>

RunWinch::RunWinch(float speed, float timeout) :
		CommandBase("RunWinch"), speed(speed), timeout(timeout) {
	if (timeout != 0) {
		SetTimeout(timeout);
	}
}
RunWinch::~RunWinch() {

}
void RunWinch::Initialize() {
	counter = 0;
	realspeed = .75;
	//MotorManager::getMotorManager()->disablePID(PID_ID_ARM);
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_1_PORT,
			realspeed);
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_2_PORT,
			realspeed);
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_3_PORT,
			realspeed);	//correct
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_4_PORT,
			realspeed);
}

void RunWinch::Execute() {
	realspeed += .005;
	if (realspeed > speed) {
		realspeed = speed;
	}
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_1_PORT,
			realspeed);
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_2_PORT,
			realspeed);
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_3_PORT,
			realspeed);	//correct
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_4_PORT,
			realspeed);
	if (counter++ > 15) {
		//drivebase->stopHold = true;
		drivebase->setLeftSpeed(0);
		drivebase->setRightSpeed(0);
		MotorManager::getMotorManager()->disablePID(PID_ID_ARM);
	}
}
bool RunWinch::IsFinished() {
	return IsTimedOut();
}
void RunWinch::Interrupted() {
	End();
}
void RunWinch::End() {
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_1_PORT, 0);
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_2_PORT, 0);
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_3_PORT, 0);
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_4_PORT, 0);
	MotorManager::getMotorManager()->disablePID(PID_ID_ARM);
}

