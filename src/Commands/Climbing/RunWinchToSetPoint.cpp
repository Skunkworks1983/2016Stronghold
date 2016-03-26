#include <Commands/Climbing/RunWinchToSetPoint.h>
#include <RobotMap.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <TuningValues.h>
#include <cstdbool>

RunWinchToSetPoint::RunWinchToSetPoint(float setPoint, float speed) :
		CommandBase("RunWinch"), setPoint(setPoint), speed(speed) {

}
RunWinchToSetPoint::~RunWinchToSetPoint() {

}
void RunWinchToSetPoint::Initialize() {
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_1_PORT,
			speed);
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_2_PORT,
			speed);
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_3_PORT,
			speed);
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_4_PORT,
			speed);
}
void RunWinchToSetPoint::Execute() {

}
bool RunWinchToSetPoint::IsFinished() {
	return SensorManager::getSensorManager()->getSensor(
			SENSOR_CLIMBER_WINCH_ENCODER)->PIDGet() < setPoint;
}
void RunWinchToSetPoint::Interrupted() {
	End();
}
void RunWinchToSetPoint::End() {
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_1_PORT, 0);
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_2_PORT, 0);
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_3_PORT, 0);
	MotorManager::getMotorManager()->setSpeed(CLIMBER_WINCH_MOTOR_4_PORT, 0);
}

