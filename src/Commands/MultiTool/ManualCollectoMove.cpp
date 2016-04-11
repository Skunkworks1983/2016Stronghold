#include <Commands/MultiTool/ManualCollectorMove.h>
#include <Services/MotorManager.h>
#include <Subsystems/Shooter.h>
#include <RobotMap.h>
#include <cstdbool>

//TODO: Find the conversion ratio for encoder ticks to degrees
ManualRotateShooter::ManualRotateShooter(float speed, float timeout) :
		speed(speed), timeout(timeout) {
	Requires(shooter);
}

void ManualRotateShooter::Initialize() {
	if(timeout != 0){
		SetTimeout(timeout);
	}
	MotorManager::getMotorManager()->disablePID(PID_ID_COLLECTOR);

	shooter->setRotatorSpeed(speed);
}

void ManualRotateShooter::Execute() {

}

bool ManualRotateShooter::IsFinished() {
	return IsTimedOut();
}

void ManualRotateShooter::End() {
	shooter->setRotatorSpeed(0);
}

void ManualRotateShooter::Interrupted() {
	End();
}
