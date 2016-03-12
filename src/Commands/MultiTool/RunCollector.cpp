#include <Commands/MultiTool/RunCollector.h>
#include <Subsystems/Shooter.h>

RunCollector::RunCollector(Shooter::rollerDirection dir, float speed,
		float timeOut) :
		dir(dir), speed(speed), timeOut(timeOut) {
	Requires(shooter);
}

void RunCollector::Initialize() {
	if (timeOut != 0) {
		SetTimeout(timeOut);
	}
	shooter->setRollerSpeed(dir, 1.0);
}

void RunCollector::Execute() {

}

bool RunCollector::IsFinished() {
	if (timeOut != 0 || dir == Shooter::KBackward) {
		return false;
	}
	return shooter->getBreakBeam();
}

void RunCollector::End() {
	shooter->setRollerSpeed(Shooter::KStop, 0);
}

void RunCollector::Interrupted() {
	End();
}
