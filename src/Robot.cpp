#include <CommandBase.h>
#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Scheduler.h>
#include <Robot.h>
#include <RobotBase.h>
#include <RobotMap.h>
#include <Services/Logger.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <Subsystems/Collector.h>
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
	MotorManager::getMotorManager()->initPIDS();
	//SensorManager::getSensorManager()->initGyro();
	CommandBase::init();
	//lw = LiveWindow::GetInstance();
	/*managePower = new ManagePower();
	 managePower->Start();

	 StallProtection *stall = new StallProtection();
	 stall->Start();*/

	//cmd = AutoBase::doRoughT();
	SmartDashboard::PutNumber("P", COLLECTOR_ROTATION_P);
	SmartDashboard::PutNumber("I", COLLECTOR_ROTATION_I);
	SmartDashboard::PutNumber("D", COLLECTOR_ROTATION_D);

}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	char str[1024];
	sprintf(str, "AutonomousInit Called");
	writeToLogFile(LOGFILE_NAME, str);

	//CommandBase::collector->setRollerSpeed(Collector::rollerDirection::KBackward, .3);
	//cmd->Start();
	//MotorManager::getMotorManager()->enablePID(PID_ID_COLLECTOR, COLLECTOR_ROTATION_ENCODER_TOP_TICKS);
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
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
	if (0 && count++ > 10) {
		double left = SensorManager::getSensorManager()->getSensor(
		SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet();
		double right = SensorManager::getSensorManager()->getSensor(
		SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet();
		//char str[1024];
		//sprintf(str, "LeftEnc %f RightEnc %f", left, right);
		//writeToLogFile(LOGFILE_NAME, str);
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
	SmartDashboard::PutNumber("Encoder",
			SensorManager::getSensorManager()->getSensor(
			SENSOR_COLLECTOR_ROTATION_ENCODER_ID)->PIDGet());
	SmartDashboard::PutNumber("WinchEncoder",
			SensorManager::getSensorManager()->getSensor(
			SENSOR_CLIMBER_WINCH_ENCODER)->PIDGet());
	SmartDashboard::PutNumber("ArmEncoder",
			SensorManager::getSensorManager()->getSensor(
			SENSOR_CLIMBER_ARM_ENCODER)->PIDGet());

}

void Robot::TestPeriodic() {
	//lw->Run();
}

START_ROBOT_CLASS(Robot);

