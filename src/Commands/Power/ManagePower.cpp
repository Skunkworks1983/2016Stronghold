#include <Commands/Power/ManagePower.h>
#include <DriverStation.h>
#include <Services/MotorManager.h>
#include <SmartDashboard/SmartDashboard.h>
#include <TuningValues.h>

ManagePower::ManagePower() {
	manager = MotorManager::getMotorManager();
}

// Called just before this Command runs the first time
void ManagePower::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ManagePower::Execute() {
	double voltage = DriverStation::GetInstance().GetBatteryVoltage();
	SmartDashboard::PutNumber("Battery Voltage", voltage);

	if (voltage >= POWER_LEVEL_1) {	//SHIELDS ARE UP CAPPIN'
		manager->setPriority(PRIORITY_ACCESSORIES);

	} else if (voltage >= POWER_LEVEL_2) {	//CUT THE SECONDARY PHASERS
		manager->setPriority(PRIORITY_SECONDARY_ACTUATORS);

	} else if (voltage >= POWER_LEVEL_3) {	//THE PRIMARY PHASERS ARE ALL WE GOT
		manager->setPriority(PRIORITY_PRIMARY_ACTUATORS);
	}

	else {	//CAPPIN' THE SHIPS RUNNIN' ON IMPULSE ONLY
		manager->setPriority(PRIORITY_DRIVEBASE);
	}

	manager->setCForAll();
	manager->setSpeedForAll();
}

// Make this return true when this Command no longer needs to run execute()
bool ManagePower::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ManagePower::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ManagePower::Interrupted() {
	End();
}
