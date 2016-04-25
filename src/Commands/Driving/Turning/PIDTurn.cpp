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

PIDTurn::PIDTurn(double target, bool absolute, double timeout) :
		target(target), absolute(absolute), timeout(timeout) {
	Requires(drivebase);
	input = target;
}

// Called just before this Command runs the first time
void PIDTurn::Initialize() {
	CommandBase::drivebase->setBrakeMode(true);

	if (AutoBase::getObstacle() == Obstacle_cheval) {
		input += 180.0;

		if (input > 360.0) {
			input = input - ((int) (input) / 360.0) * 360.0;
		}

		target = input;
	}

//ugh
	this->timeout = 2.25; //1.5 * (fabs(input == 0 ? 180 : input) / 90.0);

	if (timeout > 0) {
		SetTimeout(timeout);
	}

	MotorManager::getMotorManager()->getPID(PID_ID_DRIVEBASE_ROT)->Reset();

	if (!absolute) {
		target = input + SensorManager::getSensorManager()->getAngle()
				- (int) ((input + SensorManager::getSensorManager()->getAngle())
						/ 360.0) * 360.0;
	} else {
		//do not modify for absolute
	}

	if (fabs(input) > 90) {
		MotorManager::getMotorManager()->getPID(PID_ID_DRIVEBASE_ROT)->SetPID(
				1.0 / 100.0, 1.0 / 20000, 0);
	} else {
		MotorManager::getMotorManager()->getPID(PID_ID_DRIVEBASE_ROT)->SetPID(
				1.0 / TURN_GYRO_P, 1.0 / TURN_GYRO_I, 1.0 / TURN_GYRO_D);
	}

	/*double p = SmartDashboard::GetNumber("P", TURN_GYRO_P);
	 double i = SmartDashboard::GetNumber("I", TURN_GYRO_I);
	 double d = SmartDashboard::GetNumber("D", TURN_GYRO_D);

	 p = (p != 0 ? 1 / p : 0);
	 i = (i != 0 ? 1 / i : 0);
	 d = (d != 0 ? 1 / d : 0);

	 MotorManager::getMotorManager()->getPID(PID_ID_DRIVEBASE_ROT)->SetPID(p, i,
	 d);*/

	MotorManager::getMotorManager()->enablePID(PID_ID_DRIVEBASE_ROT, target);

	correctCount = 0;

//	drivebase->setBrakeMode(true);

	LOG_INFO("PIDTurn initialize with target: %f absolute %u timeout %f",
			MotorManager::getMotorManager()->getPID(PID_ID_DRIVEBASE_ROT)->GetSetPoint(),
			absolute, timeout);
}

// Called repeatedly when this Command is scheduled to run
void PIDTurn::Execute() {
	SmartDashboard::PutNumber("Gyro",
			SensorManager::getSensorManager()->getAngle());
	SmartDashboard::PutNumber("PIDOutput", DrivebaseMotorGroup::lastOutput);

	const double error = MotorManager::getMotorManager()->getPID(
	PID_ID_DRIVEBASE_ROT)->getError();

	LOG_INFO(
			"PIDTurn Target %f Angle %f Error %f Target %f motorPower %f runningFor %f seconds",
			MotorManager::getMotorManager()->getPID( PID_ID_DRIVEBASE_ROT)->GetSetPoint(),
			SensorManager::getSensorManager()->getAngle(), error,
			MotorManager::getMotorManager()->getPID(PID_ID_DRIVEBASE_ROT)->GetSetPoint(),
			DrivebaseMotorGroup::lastOutput, this->TimeSinceInitialized());

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

	SmartDashboard::PutNumber("GyroError", error);

	if (fabs(error) < 3.0) {
		correctCount++;
	} else {
		correctCount = 0;
	}
	return correctCount > 2 || IsTimedOut();
}

// Called once after isFinished returns true
void PIDTurn::End() {
	CommandBase::drivebase->setBrakeMode(true);
	drivebase->setLeftSpeed(0.0);
	drivebase->setRightSpeed(0.0);
	MotorManager::getMotorManager()->disablePID(PID_ID_DRIVEBASE_ROT);
//MotorManager::getMotorManager()->getPID(PID_ID_DRIVEBASE_ROT)->Reset();

	LOG_INFO("PIDTurn Ended with target %f yaw %f motorPower %f",
			MotorManager::getMotorManager()->getPID(PID_ID_DRIVEBASE_ROT)->GetSetPoint(),
			SensorManager::getSensorManager()->getAngle(),
			DrivebaseMotorGroup::lastOutput);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PIDTurn::Interrupted() {
	End();
}
