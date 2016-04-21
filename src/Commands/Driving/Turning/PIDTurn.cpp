#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/Turning/PIDTurn.h>
#include <RobotMap.h>
#include <Services/MotorGroup.h>
#include <Services/MotorManager.h>
#include <Services/PIDWrapper.h>
#include <Services/SensorManager.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Subsystems/Drivebase.h>
#include <TuningValues.h>
#include <Utility.h>
#include <cmath>

PIDTurn::PIDTurn(TurnData *d) {
	target = d->angle;
	input = target;
	Requires(drivebase);
}

PIDTurn::PIDTurn(double target, bool absolute) :
		target(target), absolute(absolute) {
	Requires(drivebase);
	input = target;
}

// Called just before this Command runs the first time
void PIDTurn::Initialize() {
	MotorManager::getMotorManager()->getPID(PID_ID_DRIVEBASE_ROT)->Reset();

	if (!absolute) {
		target = input + SensorManager::getSensorManager()->getAngle()
				- (int) ((input + SensorManager::getSensorManager()->getAngle())
						/ 360.0) * 360.0;
	}
	MotorManager::getMotorManager()->enablePID(PID_ID_DRIVEBASE_ROT, target);

	double p = SmartDashboard::GetNumber("P", TURN_GYRO_P);
	double i = SmartDashboard::GetNumber("I", TURN_GYRO_I);
	double d = SmartDashboard::GetNumber("D", TURN_GYRO_D);

	p = (p != 0 ? 1 / p : 0);
	i = (i != 0 ? 1 / i : 0);
	d = (d != 0 ? 1 / d : 0);

	MotorManager::getMotorManager()->getPID(PID_ID_DRIVEBASE_ROT)->SetPID(p, i,
			d);

	correctCount = 0;

	drivebase->setBrakeMode(false);
}

// Called repeatedly when this Command is scheduled to run
void PIDTurn::Execute() {
	SmartDashboard::PutNumber("Gyro",
			SensorManager::getSensorManager()->getAngle());

	const double error = MotorManager::getMotorManager()->getPID(
	PID_ID_DRIVEBASE_ROT)->getError();

	LOG_INFO("PIDTurn Angle %f Error %f Target %f motorPower %f",
			SensorManager::getSensorManager()->getAngle(), error, target,
			DrivebaseMotorGroup::lastOutput);

	if (fabs(error) < 15 && !first) {
		MotorManager::getMotorManager()->getPID(
		PID_ID_DRIVEBASE_ROT)->Reset();
		MotorManager::getMotorManager()->getPID(
		PID_ID_DRIVEBASE_ROT)->SetPID(1.0 / TURN_GYRO_P, 1.0 / (2000),
				1.0 / TURN_GYRO_D);
		MotorManager::getMotorManager()->getPID(
				PID_ID_DRIVEBASE_ROT)->Enable();
		first = true;
	}

}

// Make this return true when this Command no longer needs to run execute()
bool PIDTurn::IsFinished() {
	double error = MotorManager::getMotorManager()->getPID(
	PID_ID_DRIVEBASE_ROT)->getError();

//	if (fabs(error) > 180.0) {
//		if (error > 0) {
//			error = error - 180.0 + -180.0;
//		} else {
//			error = error + 180.0 - -180.0;
//		}
//	}

	SmartDashboard::PutNumber("time", GetFPGATime());
	SmartDashboard::PutNumber("GyroError", error);

	if (fabs(error) < 2.0) {
		correctCount++;
	} else {
		correctCount = 0;
	}
	return correctCount > 3;
}

// Called once after isFinished returns true
void PIDTurn::End() {
	CommandBase::drivebase->setBrakeMode(true);
	drivebase->setLeftSpeed(0.0);
	drivebase->setRightSpeed(0.0);
	MotorManager::getMotorManager()->disablePID(PID_ID_DRIVEBASE_ROT);

	LOG_INFO("PIDTurn Ended with target %f yaw %f motorPower %f", target,
			SensorManager::getSensorManager()->getYaw(),
			DrivebaseMotorGroup::lastOutput);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PIDTurn::Interrupted() {
	End();
}
