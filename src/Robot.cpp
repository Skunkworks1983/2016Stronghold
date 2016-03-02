#include <BuiltInAccelerometer.h>
#include <Commands/Autonomous/AutoBase.h>
#include <Commands/MultiTool/ActivateRollers.h>
#include <Commands/Scheduler.h>
#include <DriverStation.h>
#include <interfaces/Accelerometer.h>
#include <Robot.h>
#include <RobotBase.h>
#include <RobotMap.h>
#include <Services/Logger.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Subsystems/Climber.h>
#include <Subsystems/Collector.h>
#include <TuningValues.h>
#include <cstdbool>
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
	cmd = AutoBase::doLowB();
}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->RemoveAll();
}

void Robot::AutonomousInit() {
	Scheduler::GetInstance()->RemoveAll();
	char str[1024];
	sprintf(str, "AutonomousInit Called");
	writeToLogFile(LOGFILE_NAME, str);

	//cmd->Start();
	//rollerForward->Start();
	CommandBase::climber->setServoAngle(0);

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

	SmartDashboard::PutBoolean("BreakBeam",
			CommandBase::collector->getBreakBeam());

	//SmartDashboard::PutNumber("AbsoluteRollerEncoder", Sensor);

}

void Robot::TeleopInit() {
	Scheduler::GetInstance()->RemoveAll();
	/*char str[1024];
	 sprintf(str, "TeleOp Called");
	 writeToLogFile(LOGFILE_NAME, str);
	 sprintf(str,
	 "BatteryVoltage, leftStick, rightStick, AccelXAxis, AccelYAxis, AccelZAxis ");
	 writeToLogFile(LOGFILE_NAME, str);*/
	//rollerBackward->Start();
	//CommandBase::climber->setServoSpeed(-255);
	//CommandBase::climber->setServoAngle(0);
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();

	SmartDashboard::PutNumber("RotationEncoderRelative",
			SensorManager::getSensorManager()->getSensor(
			SENSOR_COLLECTOR_ROTATION_ENCODER_ID)->PIDGet());
	SmartDashboard::PutNumber("RotationEncoderAbsolute",
			SensorManager::getSensorManager()->getSensor(
			SENSOR_COLLECTOR_ROTATION_ENCODER_ID)->getAbsolutePosition());

	SmartDashboard::PutNumber("ArmEncoder",
			SensorManager::getSensorManager()->getSensor(
			SENSOR_CLIMBER_ARM_ENCODER)->PIDGet());

	SmartDashboard::PutNumber("ClimberArmAbsolute",
			SensorManager::getSensorManager()->getSensor(
			SENSOR_CLIMBER_ARM_ENCODER)->getAbsolutePosition());

//	char str[1024];
//	sprintf(str, "ArmEncoder %f", SensorManager::getSensorManager()->getSensor(
//	SENSOR_CLIMBER_ARM_ENCODER)->PIDGet());
//	writeToLogFile(LOGFILE_NAME, str);
}

void Robot::TestPeriodic() {
	CommandBase::climber->setServoAngle(130);
}

START_ROBOT_CLASS(Robot);

