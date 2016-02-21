#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Power/ManagePower.h>
#include <Commands/Power/StallProtection.h>
#include <Commands/Scheduler.h>
#include <Robot.h>
#include <RobotBase.h>
#include <RobotMap.h>
#include <Services/Logger.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <TuningValues.h>
#include <cstdio>

void Robot::RobotInit() {
	char nothing[1024];
	sprintf(nothing, "START OF NEW RUN \t START OF NEW RUN");
	writeToLogFile(LOGFILE_NAME, nothing);
	char str[1024];
	sprintf(str, "RobotInit Called");
	writeToLogFile(LOGFILE_NAME, str);
	MotorManager::getMotorManager();
	SensorManager::getSensorManager();
	//SensorManager::getSensorManager()->initGyro();
	CommandBase::init();
	//lw = LiveWindow::GetInstance();
	managePower = new ManagePower();
	managePower->Start();

	StallProtection *stall = new StallProtection();
	stall->Start();

	cmd = AutoBase::doRoughT();

}


void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	char str[1024];
	sprintf(str, "AutonomousInit Called");
	writeToLogFile(LOGFILE_NAME, str);
	cmd->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	char str[1024];
	sprintf(str, "TeleOp Called");
	writeToLogFile(LOGFILE_NAME, str);
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
	if (count++ > 10) {
		char str[1024];
		sprintf(str, "LeftEnc %f RightEnc %f",
				(double) SensorManager::getSensorManager()->getSensor(
				SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet(),
				(double) SensorManager::getSensorManager()->getSensor(
				SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());
		writeToLogFile(LOGFILE_NAME, str);
		/*
		 SmartDashboard::PutNumber("LeftDriveBaseEncoder",
		 SensorManager::getSensorManager()->getSensor(
		 SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
		 SmartDashboard::PutNumber("RightDriveBaseEncoder",
		 SensorManager::getSensorManager()->getSensor(
		 SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());
		 */
		count = 0;
	}
}

void Robot::TestPeriodic() {
	//lw->Run();
}

START_ROBOT_CLASS(Robot);

