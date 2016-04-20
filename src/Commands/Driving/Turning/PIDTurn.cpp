#include <Commands/Driving/Turning/PIDTurn.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <Subsystems/Drivebase.h>
#include <cstdbool>
#include <RobotMap.h>

PIDTurn::PIDTurn(double target, bool absolute) :
		target(target), absolute(absolute) {
	Requires(drivebase);
	input = target;
}

// Called just before this Command runs the first time
void PIDTurn::Initialize() {
	MotorManager::getMotorManager()->getPID(PID_ID_DRIVEBASE_ROT)->Reset();

	if (!absolute) {
		target = SensorManager::wrapCheck(
				input + SensorManager::getSensorManager()->getYaw());
	}
	MotorManager::getMotorManager()->enablePID(PID_ID_DRIVEBASE_ROT, target);

	/*double p = SmartDashboard::GetNumber("P", 120.0);
	double i = SmartDashboard::GetNumber("I", 5000.0);
	double d = SmartDashboard::GetNumber("D", 500.0);

	p = (p != 0 ? 1 / p : 0);
	i = (i != 0 ? 1 / i : 0);
	d = (d != 0 ? 1 / d : 0);

	MotorManager::getMotorManager()->getPID(PID_ID_DRIVEBASE_ROT)->SetPID(p, i,
			d);
*/
	drivebase->setBrakeMode(false);
}

// Called repeatedly when this Command is scheduled to run
void PIDTurn::Execute() {
	LOG_INFO("Angle %f Target %f", SensorManager::getSensorManager()->getYaw(),
			target);
}

// Make this return true when this Command no longer needs to run execute()
bool PIDTurn::IsFinished() {
	return MotorManager::getMotorManager()->getPID(PID_ID_DRIVEBASE_ROT)->getError() < 2.0;//MotorManager::getMotorManager()->getPID(PID_ID_DRIVEBASE_ROT)->OnTarget();
}

// Called once after isFinished returns true
void PIDTurn::End() {
	CommandBase::drivebase->setBrakeMode(true);
	drivebase->setLeftSpeed(0.0);
	drivebase->setRightSpeed(0.0);
	MotorManager::getMotorManager()->disablePID(PID_ID_DRIVEBASE_ROT);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PIDTurn::Interrupted() {
	End();
}
