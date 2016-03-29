#include <Commands/MultiTool/StopCollectorPID.h>
#include <Services/MotorManager.h>
#include <Subsystems/Shooter.h>
#include <TuningValues.h>

//TODO: Find the conversion ratio for encoder ticks to degrees
StopShooterRotationPID::StopShooterRotationPID() {
	Requires(shooter);
}

void StopShooterRotationPID::Initialize() {
	MotorManager::getMotorManager()->disablePID(PID_ID_COLLECTOR);
	//shooter->pidStopped = true;
}

void StopShooterRotationPID::Execute() {
}

bool StopShooterRotationPID::IsFinished() {
	return true;
}

void StopShooterRotationPID::End() {
	MotorManager::getMotorManager()->disablePID(PID_ID_COLLECTOR);
}

void StopShooterRotationPID::Interrupted() {
	End();
}
