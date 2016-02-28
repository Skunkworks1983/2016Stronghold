#include <Commands/Climbing/RunWinch.h>
#include <RobotMap.h>
#include <Services/MotorManager.h>
#include <Subsystems/Climber.h>
#include <Subsystems/Drivebase.h>
#include <TuningValues.h>
#include <cstdbool>

RunWinch::RunWinch(float speed) :
		CommandBase("RunWinch"), speed(speed) {
}
RunWinch::~RunWinch() {

}
void RunWinch::Initialize() {
	counter = 0;
	MotorManager::getMotorManager()->disablePID(PID_ID_ARM);
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_1_PORT, speed);
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_2_PORT, speed);
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_3_PORT,speed);	//correct
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_4_PORT,speed);
}

void RunWinch::Execute() {
	if(counter++ > 100){
		drivebase->stopHold = true;
		MotorManager::getMotorManager()->disablePID(PID_ID_ARM);
	}
}
bool RunWinch::IsFinished() {
	return false;
}
void RunWinch::Interrupted() {
	End();
}
void RunWinch::End() {
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_1_PORT, 0);
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_2_PORT, 0);
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_3_PORT, 0);
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_4_PORT, 0);
}

