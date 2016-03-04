#include <CommandBase.h>
#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Scheduler.h>
#include <DriverStation.h>
#include <OI.h>
#include <Robot.h>
#include <RobotBase.h>
#include <RobotMap.h>
#include <Services/Logger.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <SmartDashboard/SmartDashboard.h>
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
	//acc = new BuiltInAccelerometer(Accelerometer::kRange_16G);
	cmd = AutoBase::getSelectedAuto();
}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->RemoveAll();
	MotorManager::getMotorManager()->disablePID(PID_ID_ARM);
	MotorManager::getMotorManager()->disablePID(PID_ID_COLLECTOR);
}

void Robot::AutonomousInit() {
	Scheduler::GetInstance()->RemoveAll();
	char str[1024];
	sprintf(str, "AutonomousInit Called");
	writeToLogFile(LOGFILE_NAME, str);

	cmd->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();

	/*double left = SensorManager::getSensorManager()->getSensor(
	 SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet();
	 double right = SensorManager::getSensorManager()->getSensor(
	 SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet();

	 char str[1024];
	 sprintf(str, "LeftEncoder %f, RightEncoder %f", left, right);
	 writeToLogFile(LOGFILE_NAME, str);*/

	//SmartDashboard::PutNumber("AbsoluteRollerEncoder", Sensor);
}

void Robot::TeleopInit() {
	Scheduler::GetInstance()->RemoveAll();
	char str[1024];
	sprintf(str, "TeleOp Called");
	writeToLogFile(LOGFILE_NAME, str);

	sprintf(str, "BatteryVoltage, leftStick, rightStick");
	writeToLogFile(LOGFILE_NAME, str);
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();

//	SmartDashboard::PutNumber("RotationEncoderRelative",
//			SensorManager::getSensorManager()->getSensor(
//			SENSOR_COLLECTOR_ROTATION_ENCODER_ID)->PIDGet());
//	SmartDashboard::PutNumber("RotationEncoderAbsolute",
//			SensorManager::getSensorManager()->getSensor(
//			SENSOR_COLLECTOR_ROTATION_ENCODER_ID)->getAbsolutePosition());
//
//	SmartDashboard::PutNumber("ArmEncoder",
//			SensorManager::getSensorManager()->getSensor(
//			SENSOR_CLIMBER_ARM_ENCODER)->PIDGet());
//
//	SmartDashboard::PutNumber("ClimberArmAbsolute",
//			SensorManager::getSensorManager()->getSensor(
//			SENSOR_CLIMBER_ARM_ENCODER)->getAbsolutePosition());

	double voltage = DriverStation::GetInstance().GetBatteryVoltage();

	char str[1024];
	sprintf(str, "%f,%f,%f", voltage, CommandBase::oi->getLeftStickY(),
			CommandBase::oi->getRightStickY());
	writeToLogFile(LOGFILE_NAME, str);

//	char str[1024];
//	sprintf(str, "ArmEncoder %f", SensorManager::getSensorManager()->getSensor(
//	SENSOR_CLIMBER_ARM_ENCODER)->PIDGet());
//	writeToLogFile(LOGFILE_NAME, str);

}

void Robot::TestPeriodic() {

}

START_ROBOT_CLASS(Robot);

