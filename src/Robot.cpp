#include <Commands/Driving/TurnRightEncoder.h>
#include <Commands/Scheduler.h>
#include <DriverStation.h>
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
	MotorManager::getMotorManager();
	SensorManager::getSensorManager();
	MotorManager::getMotorManager()->initPIDS();

	CommandBase::init();
	//SensorManager::getSensorManager()->initGyro();

	//managePower = new ManagePower();
	//managePower->Start();

	//StallProtection *stall = new StallProtection();
	//stall->Start();

	//cmd = AutoBase::doRoughT();
}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	Scheduler::GetInstance()->RemoveAll();
	char str[1024];
	sprintf(str, "AutonomousInit Called");
	writeToLogFile(LOGFILE_NAME, str);
	/*pidGyroTest = new PIDGyroTest();
	 pidGyroTest->Start();
	 TAKE OUT COMMENTS TO TEST GYRO*/
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
	char str[1024];
		sprintf(str, "leftEncoder %f, rightEncoder %f",
				SensorManager::getSensorManager()->getSensor(
				SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet(),
				SensorManager::getSensorManager()->getSensor(
				SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());
		writeToLogFile(LOGFILE_NAME, str);
}

void Robot::TeleopInit() {
	Scheduler::GetInstance()->RemoveAll();
	char str[1024];
	sprintf(str, "TeleOp Called");
	writeToLogFile(LOGFILE_NAME, str);

	/*MotorManager::getMotorManager()->setSpeed(COLLECTOR_ROTATOR_MOTOR_LEFT_PORT,
	 .1);
	 MotorManager::getMotorManager()->setSpeed(
	 COLLECTOR_ROTATOR_MOTOR_RIGHT_PORT, .1);
	 */
	//MotorManager::getMotorManager()->enablePID(PID_ID_COLLECTOR, COLLECTOR_ROTATION_ENCODER_FLOOR_TICKS);
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
	double voltage = DriverStation::GetInstance().GetBatteryVoltage();

	//char str[1024];
	//sprintf(str, "BatteryVoltage %f", voltage);
	//writeToLogFile(LOGFILE_NAME, str);

	char str[1024];
	sprintf(str, "leftEncoder %f, rightEncoder %f",
			SensorManager::getSensorManager()->getSensor(
			SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet(),
			SensorManager::getSensorManager()->getSensor(
			SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());
	writeToLogFile(LOGFILE_NAME, str);

}

void Robot::TestPeriodic() {
	//lw->Run();
}

START_ROBOT_CLASS(Robot);

