#include <Commands/Driving/TankDrive.h>
#include <DriverStation.h>
#include <OI.h>
#include <RobotMap.h>
#include <Services/MotorManager.h>
#include <Subsystems/Drivebase.h>
#include <cmath>

TankDrive::TankDrive() {
	Requires(drivebase);
}

// Called just before this Command runs the first time
void TankDrive::Initialize() {
	/*MotorManager::getMotorManager()->getMotor(
	 DRIVEBASE_LEFTMOTOR_1_PORT)->setBrakeMode(true);
	 MotorManager::getMotorManager()->getMotor(
	 DRIVEBASE_LEFTMOTOR_2_PORT)->setBrakeMode(true);
	 MotorManager::getMotorManager()->getMotor(
	 DRIVEBASE_LEFTMOTOR_3_PORT)->setBrakeMode(true);
	 MotorManager::getMotorManager()->getMotor(
	 DRIVEBASE_RIGHTMOTOR_1_PORT)->setBrakeMode(true);
	 MotorManager::getMotorManager()->getMotor(
	 DRIVEBASE_RIGHTMOTOR_2_PORT)->setBrakeMode(true);
	 MotorManager::getMotorManager()->getMotor(
	 DRIVEBASE_RIGHTMOTOR_3_PORT)->setBrakeMode(true);
	 */
}

// Called repeatedly when this Command is scheduled to run
void TankDrive::Execute() {
	if (drivebase->isDriverControl()
			&& DriverStation::GetInstance().IsOperatorControl()
			&& !DriverStation::GetInstance().IsAutonomous()) {
		if (oi->isJoystickButtonPressed(0, 1)) {
			const double oiLeft = oi->getLeftStickY();
			const double oiRight = oiLeft; //oi->getRightStickY();

			drivebase->setLeftSpeed(oiLeft);
			drivebase->setRightSpeed(oiRight);

			const float l1 = MotorManager::getMotorManager()->getMotor(
			DRIVEBASE_LEFTMOTOR_1_PORT)->talon->GetOutputCurrent();
			const float l2 = MotorManager::getMotorManager()->getMotor(
			DRIVEBASE_LEFTMOTOR_2_PORT)->talon->GetOutputCurrent();
			const float l3 = MotorManager::getMotorManager()->getMotor(
			DRIVEBASE_LEFTMOTOR_3_PORT)->talon->GetOutputCurrent();

			const float r1 = MotorManager::getMotorManager()->getMotor(
			DRIVEBASE_RIGHTMOTOR_1_PORT)->talon->GetOutputCurrent();
			const float r2 = MotorManager::getMotorManager()->getMotor(
			DRIVEBASE_RIGHTMOTOR_2_PORT)->talon->GetOutputCurrent();
			const float r3 = MotorManager::getMotorManager()->getMotor(
			DRIVEBASE_RIGHTMOTOR_3_PORT)->talon->GetOutputCurrent();

			//LOG_INFO("USING ONLY ONE CIM %f %f", oiLeft, oiRight);
			//LOG_INFO("%f %f %f %f %f %f", l1, l2, l3, r1, r2, r3);
		} else {
			if (!driveState) {
				driveState = true;
			}
			drivebase->setLeftSpeed(oi->getLeftStickY());
			drivebase->setRightSpeed(oi->getRightStickY());
		}

		if (oi->getLeftStickY() > .5) {
			drivebase->setHold(false);
		}
		if (fabs(oi->getLeftStickY()) > .8 || fabs(oi->getRightStickY()) > .8) {
			drivebase->setDriverControl(true);
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool TankDrive::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void TankDrive::End() {
	drivebase->setLeftSpeed(0);
	drivebase->setRightSpeed(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TankDrive::Interrupted() {
	End();
}
