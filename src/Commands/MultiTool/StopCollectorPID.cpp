#include <Commands/MultiTool/StopCollectorPID.h>
#include <Services/MotorManager.h>
#include <Subsystems/Collector.h>
#include <TuningValues.h>

//TODO: Find the conversion ratio for encoder ticks to degrees
StopCollectorPID::StopCollectorPID() {

}

void StopCollectorPID::Initialize() {
	MotorManager::getMotorManager()->disablePID(PID_ID_COLLECTOR);
	//collector->pidStopped = true;
}

void StopCollectorPID::Execute() {
}

bool StopCollectorPID::IsFinished() {
	return true;
}

void StopCollectorPID::End() {

}

void StopCollectorPID::Interrupted() {
	End();
}
