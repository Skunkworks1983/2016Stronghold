#include <Commands/MultiTool/StopCollectorPID.h>
#include <Services/MotorManager.h>
#include <Subsystems/Shooter.h>
#include <TuningValues.h>

//TODO: Find the conversion ratio for encoder ticks to degrees
StopShooterRotationPID::StopShooterRotationPID() {

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

}

void StopShooterRotationPID::Interrupted() {
	End();
}
