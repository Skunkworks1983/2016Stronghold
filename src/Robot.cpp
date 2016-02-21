#include <Commands/Power/ManagePower.h>
#include <Robot.h>
#include <RobotBase.h>
#include <RobotMap.h>
#include <Services/Logger.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <TuningValues.h>
#include <cstdio>

void Robot::RobotInit() {
	char startup[1024];
	sprintf(startup, "START OF NEW RUN \t START OF NEW RUN");
	writeToLogFile(LOGFILE_NAME, startup);
	char str[1024];
	sprintf(str, "RobotInit Called");
	writeToLogFile(LOGFILE_NAME, str);
	motorManager = MotorManager::getMotorManager(); //Not sure why these were the other way, so I changed them to the
	sensorManager = SensorManager::getSensorManager(); //way I know, change back if this isn't what you wanted.
	CommandBase::init();
	//lw = LiveWindow::GetInstance();
	managePower = new ManagePower();
	managePower->Start();
}


void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	char str[1024];
	sprintf(str, "AutonomousInit Called");
	writeToLogFile(LOGFILE_NAME, str);
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
	if (count++ > 10 && DEBUG) { //Every 10 iterations of Teleop, and only if the robot is in debug mode.
		char str[1024];
		sprintf(str, "LeftEnc %f RightEnc %f",
				(double) sensorManager->getSensor(
				SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet(),
				(double) sensorManager->getSensor(
				SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());
		writeToLogFile(LOGFILE_NAME, str);

		SmartDashboard::PutNumber("LeftDriveBaseEncoder", sensorManager->getSensor(
				SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
		SmartDashboard::PutNumber("RightDriveBaseEncoder", sensorManager->getSensor(
				SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());

		count = 0;
	}
}

void Robot::TestPeriodic() {
	//lw->Run();
}

START_ROBOT_CLASS(Robot);

